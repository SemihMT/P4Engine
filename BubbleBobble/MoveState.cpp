#include "MoveState.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "FallState.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpState.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "TimeManager.h"

dae::MoveState::MoveState(GameObject* owner) :
	State{ owner },
	m_transform(GetOwner()->GetTransform()),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>()),
	m_rb(GetOwner()->GetComponent<RigidBodyComponent>()),
	m_collider(GetOwner()->GetComponent<ColliderComponent>())
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
	Notify(Event::Player_Move,{});
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
	if(m_rb->GetVerticalVelocity() > 0)
	{
		std::unique_ptr<State> fallState = std::make_unique<FallState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(fallState));
	}
}
