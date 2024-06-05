#include "MoveState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpState.h"
#include "RigidBodyComponent.h"

dae::MoveState::MoveState(GameObject* owner):State{ owner }
{
}

dae::MoveState::~MoveState()
{
}

void dae::MoveState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Walk");
	}
}

void dae::MoveState::OnExit()
{

}

void dae::MoveState::Update()
{
	if (!(InputManager::GetInstance().IsDown(SDLK_LEFT) || InputManager::GetInstance().IsDown(SDLK_RIGHT)))
	{
		OnExit();
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner());
		idleState->OnEnter();
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
		return;
	}

	if(!GetOwner()->GetComponent<ColliderComponent>()->IsCollidingBottom())
	{
		OnExit();
		std::unique_ptr<State> jumpState = std::make_unique<JumpState>(GetOwner());
		jumpState->OnEnter();
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(jumpState));
		
	}

}
