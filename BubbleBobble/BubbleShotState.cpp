#include "BubbleShotState.h"

#include "AnimationComponent.h"
#include "BubbleEventHandlerComponent.h"
#include "BubbleIdleState.h"
#include "StateComponent.h"
#include "TimeManager.h"

dae::BubbleShotState::BubbleShotState(GameObject* owner, Transform* playerTransform) :
	State(owner),
	m_playerTransform{ playerTransform },
	m_bubbleComponent(GetOwner()->GetComponent<BubbleComponent>())
{
}

dae::BubbleShotState::~BubbleShotState()
{
}

void dae::BubbleShotState::OnEnter()
{
	if (std::is_base_of_v<Observer, BubbleEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<BubbleEventHandlerComponent>());
	Notify(Event::Bubble_Shot, {});

	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubbleIdle");
	}

	m_bubbleComponent->SetIsAvailable(false);

	m_initialPlayerPos = m_playerTransform->GetWorldPosition();
	m_playerForward = m_playerTransform->GetForwardDirection();
	const auto bubbleShootPos = m_initialPlayerPos + glm::vec3{ 32,0,0 } *m_playerForward;
	GetOwner()->GetTransform()->SetLocalPosition(bubbleShootPos);
}

void dae::BubbleShotState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<BubbleEventHandlerComponent>());
}

void dae::BubbleShotState::Update()
{
	const float dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
	GetOwner()->GetTransform()->Translate(m_bubbleComponent->GetSpeed() * dt * m_playerForward);
	m_bubbleLifetimeTimer += dt;
	if (abs(GetOwner()->GetTransform()->GetLocalPosition().x - m_initialPlayerPos.x) >= m_bubbleComponent->GetMoveDistance()
		|| m_bubbleLifetimeTimer >= m_maxBubbleLifetime )
	{
		GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<BubbleIdleState>(GetOwner()));
	}
}
