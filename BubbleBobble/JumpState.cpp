#include "JumpState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "FallState.h"
#include "IdleState.h"
#include "InputManager.h"
#include "MoveState.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "StateComponent.h"

dae::JumpState::JumpState(GameObject* owner) :
	State(owner),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>()),
	m_rb{ GetOwner()->GetComponent<RigidBodyComponent>() }
{
}

dae::JumpState::~JumpState()
{
}

void dae::JumpState::OnEnter()
{
	//Add the event handler as the observer so it gets notified of events
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
	Notify(Event::Player_Jump, {});

	//Debug
	std::cout << "Entered Jump state\n";

	m_animationComponent->SetCurrentAnimation("JumpUp");
	m_rb->Jump();
}

void dae::JumpState::OnExit()
{
	std::cout << "Exiting Jump state\n";
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::JumpState::Update()
{
	if (GetOwner()->GetComponent<RigidBodyComponent>()->GetVerticalVelocity() < 0)
	{
		std::cout << "jumping upwards\n";
		GetOwner()->GetComponent<ColliderComponent>()->StartJumping();
		//Disable collision when jumping up
		//GetOwner()->GetComponent<ColliderComponent>()->SetTopBottomCollision(false);
	}
	else
	{
		GetOwner()->GetComponent<ColliderComponent>()->Land();
		std::unique_ptr<State> fallState = std::make_unique<FallState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(fallState));
		return;
	}


	auto worldPos = GetOwner()->GetTransform()->GetWorldPosition();
	if (worldPos.y > 464)
	{
		GetOwner()->GetTransform()->SetLocalPosition(worldPos.x, 0, worldPos.z);
	}


}
