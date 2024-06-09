#pragma once
#include "Command.h"
#include "LevelParser.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "ScoreObserverComponent.h"
#include "HealthObserverComponent.h"
namespace dae
{
	class NextLevelCommand : public Command
	{
	public:
		void Execute() override
		{
			auto currentLevel = SceneManager::GetInstance().GetCurrentScene();
			auto healthUI = currentLevel->GetGameObject("HealthObserver");
			auto h = currentLevel->Pop(healthUI);
			auto scoreUI = currentLevel->GetGameObject("ScoreObserver");
			auto s = currentLevel->Pop(scoreUI);

			currentLevel->RemoveAll();

			h->GetComponent<HealthObserverComponent>()->Init(3,3);
			currentLevel->Add(std::unique_ptr<GameObject>(h));
			s->GetComponent<ScoreObserverComponent>()->Init(0,0);
			currentLevel->Add(std::unique_ptr<GameObject>(s));

			auto levelName = currentLevel->GetName();
			if (levelName == "1")
			{
				currentLevel->SetName("2");
				switch(GameSettings::GetInstance().GetGameState())
				{
				case GameSettings::GameState::Singleplayer:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level2Singleplayer.ppm");
					break;
				case GameSettings::GameState::Coop:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level2.ppm");
					break;
				case GameSettings::GameState::Versus:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/Versus.ppm");
					break;
				}
				
				
			}
			else if (levelName == "2")
			{
				currentLevel->SetName("3");
				switch(GameSettings::GetInstance().GetGameState())
				{
				case GameSettings::GameState::Singleplayer:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level3Singleplayer.ppm");
					break;
				case GameSettings::GameState::Coop:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level3.ppm");
					break;
				case GameSettings::GameState::Versus:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/Versus.ppm");
					break;
				}
			}
			else if (levelName == "3")
			{
				currentLevel->SetName("1");
				switch(GameSettings::GetInstance().GetGameState())
				{
				case GameSettings::GameState::Singleplayer:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level1Singleplayer.ppm");
					break;
				case GameSettings::GameState::Coop:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level1.ppm");
					break;
				case GameSettings::GameState::Versus:
					GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/Versus.ppm");
					break;
				}
			}
		}
	};
}
