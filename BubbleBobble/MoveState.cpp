#include "MoveState.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpState.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "TimeManager.h"

dae::MoveState::MoveState(GameObject* owner, const glm::vec3& direction, float speed) :
	State{ owner },
	m_transform(GetOwner()->GetTransform()),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>()),
	m_rb(GetOwner()->GetComponent<RigidBodyComponent>()),
	m_collider(GetOwner()->GetComponent<ColliderComponent>()),
	m_direction(direction),
	m_speed(speed)
{
}

dae::MoveState::~MoveState()
{
}

void dae::MoveState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());

	m_animationComponent->SetCurrentAnimation("Walk");
	std::cout << "Entered Move state\n";
	//GetOwner()->GetComponent<RigidBodyComponent>()->SetShouldFall(false);
	//GetOwner()->GetComponent<ColliderComponent>()->SetTopBottomCollision(true);
}

void dae::MoveState::OnExit()
{
	std::cout << "Exited Move state\n";
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::MoveState::Update()
{
	if (!(InputManager::GetInstance().IsDown(SDLK_LEFT) || InputManager::GetInstance().IsDown(SDLK_RIGHT)))
	{
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
		return;
	}

	m_transform->SetForwardDirection(m_direction);
	bool goingLeftWhileTouchingLeft = m_collider->IsCollidingLeft() && m_direction == glm::vec3{ -1,0,0 };
	bool goingRightWhileTouchingRight = m_collider->IsCollidingRight() && m_direction == glm::vec3{ 1,0,0 };

	if (!(goingLeftWhileTouchingLeft && goingRightWhileTouchingRight))
	{
		m_transform->Translate(m_direction * static_cast<float>(TimeManager::GetInstance().DeltaTime()) * m_speed);
	}

}
