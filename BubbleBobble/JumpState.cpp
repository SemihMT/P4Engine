#include "JumpState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "IdleState.h"
#include "InputManager.h"
#include "MoveState.h"
#include "StateComponent.h"

dae::JumpState::JumpState(GameObject* owner) : State(owner)
{
	OnEnter();
}

dae::JumpState::~JumpState()
{
	OnExit();
}

void dae::JumpState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Jump");
	}
}

void dae::JumpState::OnExit()
{
}

void dae::JumpState::Update()
{
	if (!GetOwner()->GetComponent<ColliderComponent>()->IsColliding().empty())
	{
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
	}
	else
	{
		auto worldPos = GetOwner()->GetTransform()->GetWorldPosition();
		if (worldPos.y > 464)
		{
			GetOwner()->GetTransform()->SetLocalPosition(worldPos.x, 0, worldPos.z);
		}
	}

}
