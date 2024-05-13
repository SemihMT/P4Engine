#include "IdleState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "JumpState.h"
#include "MoveState.h"
#include "PhysicsComponent.h"

dae::IdleState::IdleState(GameObject* owner):State{ owner }
{
	OnEnter();
}

dae::IdleState::~IdleState()
{
	OnExit();
}

void dae::IdleState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Idle");
	}
}

void dae::IdleState::OnExit()
{

}

void dae::IdleState::Update()
{
	const auto playerIsMoving = 
		InputManager::GetInstance().IsDown(SDLK_LEFT) ||
		InputManager::GetInstance().IsDown(SDLK_RIGHT);

	if (playerIsMoving)
	{
		std::unique_ptr<State> moveState = std::make_unique<MoveState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(moveState));
		return;
	}
	if(GetOwner()->GetComponent<ColliderComponent>()->IsColliding().empty())
	{
		std::unique_ptr<State> jumpState = std::make_unique<JumpState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(jumpState));
	}
}
