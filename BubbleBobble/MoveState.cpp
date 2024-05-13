#include "MoveState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpState.h"
#include "PhysicsComponent.h"

dae::MoveState::MoveState(GameObject* owner):State{ owner }
{
	OnEnter();
}

dae::MoveState::~MoveState()
{
	OnExit();
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
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
		return;
	}

	if(GetOwner()->GetComponent<ColliderComponent>()->IsColliding().empty())
	{
		std::unique_ptr<State> jumpState = std::make_unique<JumpState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(jumpState));
		
	}

}
