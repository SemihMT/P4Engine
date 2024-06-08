#include "BubbleSpawnState.h"

#include "AnimationComponent.h"
#include "BubbleEventHandlerComponent.h"
#include "BubbleMovementComponent.h"
#include "ColliderComponent.h"

dae::BubbleSpawnState::BubbleSpawnState(GameObject* owner) :
	State(owner)
{
}

dae::BubbleSpawnState::~BubbleSpawnState()
{
}

void dae::BubbleSpawnState::OnEnter()
{
	if (std::is_base_of_v<Observer, BubbleEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<BubbleEventHandlerComponent>());

	Notify(Event::Bubble_Spawn,{});
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubbleIdle");
	}
	GetOwner()->GetTransform()->SetLocalPosition(-100.0,-100.0,0);
}

void dae::BubbleSpawnState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<BubbleEventHandlerComponent>());
}

void dae::BubbleSpawnState::Update()
{
}
