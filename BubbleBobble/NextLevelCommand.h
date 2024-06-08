#pragma once
#include "Command.h"
#include "LevelParser.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
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
			currentLevel->Add(std::unique_ptr<GameObject>(h));
			currentLevel->Add(std::unique_ptr<GameObject>(s));

			auto levelName = currentLevel->GetName();
			if (levelName == "1")
			{
				currentLevel->SetName("2");
				GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level2.ppm");
			}
			else if (levelName == "2")
			{
				currentLevel->SetName("3");
				GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level3.ppm");
			}
			else if (levelName == "3")
			{
				currentLevel->SetName("1");
				GameSettings::GetInstance().GetParser()->Parse(currentLevel, "Levels/level1.ppm");
			}
		}
	};
}
