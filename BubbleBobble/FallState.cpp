#include "FallState.h"

#include "AnimationComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "ColliderComponent.h"
#include "IdleState.h"
#include "RigidBodyComponent.h"

dae::FallState::FallState(GameObject* owner) : State(owner)
{
}

dae::FallState::~FallState()
{
}

void dae::FallState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("FallDown");
	}
	std::cout << "Entered Fall state\n";
	Notify(Event::Player_Fall,{});


	GetOwner()->GetComponent<ColliderComponent>()->Land();

}

void dae::FallState::OnExit()
{
	std::cout << "Exited Fall state\n";
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::FallState::Update()
{
	if (GetOwner()->GetComponent<ColliderComponent>()->IsCollidingBottom())
	{
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
		return;
	}
}
