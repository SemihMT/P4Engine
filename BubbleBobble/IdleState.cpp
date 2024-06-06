#include "IdleState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "JumpState.h"
#include "MoveState.h"
#include "PlayerComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"

dae::IdleState::IdleState(GameObject* owner) :State{ owner }
{

}

dae::IdleState::~IdleState()
{
}

void dae::IdleState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());

	Notify(Event::Player_Idle,{});
	std::cout << "Entered Idle state\n";

	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Idle");
	}

	//GetOwner()->GetComponent<ColliderComponent>()->SetTopBottomCollision(true);
	//GetOwner()->GetComponent<RigidBodyComponent>()->SetShouldFall(false);
}

void dae::IdleState::OnExit()
{
	std::cout << "Exit Idle state\n";
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::IdleState::Update()
{
}
