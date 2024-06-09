#include "MaitaChaseState.h"

#include "BoulderComponent.h"
#include "SceneManager.h"
#include "TimeManager.h"

dae::MaitaChaseState::MaitaChaseState(GameObject* owner)
	:
	State(owner),
	m_ownerTransform(GetOwner()->GetTransform()),
	m_ownerRb(GetOwner()->GetComponent<RigidBodyComponent>()),
	m_ownerCollider(GetOwner()->GetComponent<ColliderComponent>()),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>())
{
}

dae::MaitaChaseState::~MaitaChaseState()
{
}

void dae::MaitaChaseState::OnEnter()
{
	GetOwner()->SetName("Maita");
	m_animationComponent->SetCurrentAnimation("Walk");

	m_chosenPlayer = SceneManager::GetInstance().GetCurrentScene()->GetGameObject("Player");
	m_directionToPlayer = m_chosenPlayer->GetTransform()->GetWorldPosition() - GetOwner()->GetTransform()->GetWorldPosition();
	m_directionToPlayer = glm::normalize(m_directionToPlayer);
}

void dae::MaitaChaseState::OnExit()
{
}

void dae::MaitaChaseState::Update()
{
	const float dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
    glm::vec2 ownerPos = m_ownerTransform->GetWorldPosition();

    //Decide on an action every 3 seconds
    //Jump, Follow the chosen player or go in a random direction
    m_timeSinceLastDecision += dt;
    if (m_timeSinceLastDecision >= m_decisionInterval) {
        m_timeSinceLastDecision = 0.0f;
        DecideNextAction();
    }

    m_angryTimer += dt;
    if(m_angryTimer >= m_timeUntilAngry && GetOwner()->GetComponent<AnimationComponent>()->GetCurrentAnimationName() != "AngryWalk")
    {
	    GetOwner()->GetComponent<AnimationComponent>()->SetCurrentAnimation("AngryWalk");
        m_speed *= 1.25f;
        m_decisionInterval = 2;
    }

    // Execute actions based on decisions
    if (m_shouldJump) {
        Jump();
    } else {
        if (m_horizontalDirection == glm::vec2{1,0}) {
            MoveRight(dt);
        } else if (m_horizontalDirection == glm::vec2{-1,0}) {
            MoveLeft(dt);
        }
    }

    if (m_ownerRb->GetVerticalVelocity() > 0) {
        m_ownerCollider->Land();
    }

    // Recalculate direction to player for continuous movement
    m_directionToPlayer = m_chosenPlayer->GetTransform()->GetWorldPosition() - m_ownerTransform->GetWorldPosition();
    m_directionToPlayer = glm::normalize(m_directionToPlayer);
}

void dae::MaitaChaseState::DecideNextAction()
{
     m_shouldJump = (m_directionToPlayer.y < 0) || (GetRandomFloat() < 0.02f);

    if (!m_shouldJump) {
        if (GetRandomFloat() < 0.85f) {
            m_horizontalDirection = (GetRandomFloat() < 0.5f) ? glm::vec2{1,0} : glm::vec2{-1,0};
            Shoot();
        } else {
            // Follow the player
            m_horizontalDirection = (m_directionToPlayer.x > 0) ? glm::vec2{1,0} : glm::vec2{-1,0};
        }
    } else {
        m_horizontalDirection = {0,0};
    }
}

void dae::MaitaChaseState::MoveRight(float dt)
{
    
	m_ownerTransform->Translate(m_speed * dt, 0, 0);
    m_ownerTransform->SetForwardDirection({1,0,0});
}

void dae::MaitaChaseState::MoveLeft(float dt)
{
    m_ownerTransform->Translate(-m_speed * dt, 0, 0);
    m_ownerTransform->SetForwardDirection({-1,0,0});
}

void dae::MaitaChaseState::Jump()
{
    m_ownerRb->Jump();
	m_ownerCollider->StartJumping();
}

void dae::MaitaChaseState::Shoot()
{
    auto boulder = std::make_unique<GameObject>(m_ownerTransform->GetLocalPosition());
    boulder->SetName("Boulder");
    boulder->AddComponent<BoulderComponent>(m_ownerTransform->GetForwardDirection());

    SceneManager::GetInstance().GetCurrentScene()->Add(std::move(boulder));
}
