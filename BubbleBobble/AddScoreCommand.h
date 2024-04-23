#pragma once
#include "GameObjectCommand.h"
#include "ScoreComponent.h"
namespace dae
{
	class AddScoreCommand final : public GameObjectCommand
	{
	public:
		AddScoreCommand(GameObject* gameObject)
			: GameObjectCommand(gameObject)
		{
		}

		void Execute() override
		{
			if (auto* scoreComp = GetGameObject()->GetComponent<ScoreComponent>())
			{
				scoreComp->AddToScore(100);
			}
		}
	};
}
