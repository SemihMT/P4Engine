#pragma once
#include "GameObject.h"
#include "GameObjectCommand.h"
#include "JumpState.h"
#include "PlayerComponent.h"
#include "StateComponent.h"
namespace dae
{
	class MaitaJumpCommand final : public GameObjectCommand
	{
	public:
		MaitaJumpCommand(GameObject* gameObject)
			: GameObjectCommand(gameObject)
		{
		}
		void Execute() override
		{
			GetGameObject()->GetComponent<RigidBodyComponent>()->Jump();
			GetGameObject()->GetComponent<ColliderComponent>()->StartJumping();
		}
	};
}
