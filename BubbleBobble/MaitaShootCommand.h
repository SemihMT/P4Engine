#pragma once
#include "GameObjectCommand.h"
#include "MaitaVersusComponent.h"


namespace dae
{
	class MaitaShootCommand final : public GameObjectCommand
	{
	public:
		MaitaShootCommand(GameObject* gameObject) : GameObjectCommand(gameObject)
		{
		}
		void Execute() override
		{
			GetGameObject()->GetComponent<MaitaVersusComponent>()->Shoot();
		}

	};
}
