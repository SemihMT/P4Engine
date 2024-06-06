#pragma once
#include "GameObject.h"
#include "GameObjectCommand.h"
#include "JumpState.h"
#include "TimeManager.h"
#include "RigidBodyComponent.h"
namespace dae
{
	class JumpCommand final : public GameObjectCommand
	{
	public:
		JumpCommand(GameObject* gameObject)
			: GameObjectCommand(gameObject)
		{
		}
		void Execute() override
		{
			GetGameObject()->GetComponent<StateComponent>()->SetState(std::make_unique<JumpState>(GetGameObject()));
		}
	};
}
