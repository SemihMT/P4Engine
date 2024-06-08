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

dae::JumpState::JumpState(GameObject* owner, int playerNumber) :
	State(owner),
	m_playerNumber(playerNumber),
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

	m_animationComponent->SetCurrentAnimation("JumpUp");
	m_rb->Jump();
}

void dae::JumpState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::JumpState::Update()
{
	if (GetOwner()->GetComponent<RigidBodyComponent>()->GetVerticalVelocity() < 0)
	{
		std::cout << "jumping upwards\n";
		GetOwner()->GetComponent<ColliderComponent>()->StartJumping();
	}
	else
	{
		GetOwner()->GetComponent<ColliderComponent>()->Land();
		std::unique_ptr<State> fallState = std::make_unique<FallState>(GetOwner(), m_playerNumber);
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(fallState));
	}
}
