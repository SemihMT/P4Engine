#pragma once
#include "GameObjectCommand.h"
#include "ShootBubble.h"
#include "ShootState.h"

namespace dae
{
	class ShootCommand final : public GameObjectCommand
	{
	public:
		ShootCommand(GameObject* gameObject) : GameObjectCommand(gameObject)
		{
		}
		void Execute() override
		{
			GetGameObject()->GetComponent<StateComponent>()->SetState(std::make_unique<ShootState>(GetGameObject(), GetGameObject()->GetComponent<PlayerComponent>()->GetPlayerNumber()));
		}

	};
}
