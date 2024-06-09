#include "GameSettings.h"

#include "HealthObserverComponent.h"
#include "LevelEndCheckerComponent.h"
#include "SceneManager.h"
#include "ScoreObserverComponent.h"
#include "SpriteComponent.h"
#include "Text.h"
#include "TextureComponent.h"

namespace dae
{
	void GameSettings::Init()
	{
		m_parser = std::make_unique<LevelParser>();
	}

	void GameSettings::SetGameState(GameState type, int level)
	{
		m_gameType = type;

		switch (m_gameType)
		{
		case GameState::Selection:

			break;
		case GameState::Singleplayer:
			CreateSingleplayerScene(level);
			break;
		case GameState::Coop:
			CreateMultiplayerScene(level);
			break;
		case GameState::Versus:
			CreateVersusScene();
			break;
		case GameState::Gameover:
			CreateGameOverScene();
			break;
		}
	}

	void GameSettings::SetChangeLevelFlag(int level)
	{
		m_changeLevelFlag = true;
		m_newLevel = level;
	}


	void GameSettings::Update()
	{
		if (m_changeLevelFlag)
		{
			m_changeLevelFlag = false;
			if (m_gameType == GameState::Singleplayer)
				CreateSingleplayerScene(m_newLevel);
			if (m_gameType == GameState::Coop)
				CreateMultiplayerScene(m_newLevel);
		}
	}

	void GameSettings::CreateSingleplayerScene(int level)
	{
		SceneManager::GetInstance().RemoveScene(std::to_string(level - 1));
		auto& levelScene = SceneManager::GetInstance().CreateScene(std::to_string(level));
		SceneManager::GetInstance().SetCurrentScene(std::to_string(level));

		const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
		const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
		const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);

		auto scoreUI = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
		scoreUI->SetName("ScoreObserver");
		scoreUI->AddComponent<Text>(smallFont, " ");
		scoreUI->AddComponent<ScoreObserverComponent>();
		levelScene.Add(std::move(scoreUI));

		auto healthUI = std::make_unique<GameObject>(glm::vec3{ 0,400,0 });
		healthUI->SetName("HealthObserver");
		healthUI->AddComponent<Text>(smallFont, " ");
		healthUI->AddComponent<HealthObserverComponent>();
		levelScene.Add(std::move(healthUI));

		m_parser->Parse(&levelScene, "Levels/level" + std::to_string(level) + "Singleplayer.ppm");

	}

	void GameSettings::CreateMultiplayerScene(int level)
	{
		SceneManager::GetInstance().RemoveScene(std::to_string(level - 1));
		auto& levelScene = SceneManager::GetInstance().CreateScene(std::to_string(level));
		SceneManager::GetInstance().SetCurrentScene(std::to_string(level));

		const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
		const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
		const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);

		auto scoreUI = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
		scoreUI->SetName("ScoreObserver");
		scoreUI->AddComponent<Text>(smallFont, " ");
		scoreUI->AddComponent<ScoreObserverComponent>();
		levelScene.Add(std::move(scoreUI));

		auto healthUI = std::make_unique<GameObject>(glm::vec3{ 0,400,0 });
		healthUI->SetName("HealthObserver");
		healthUI->AddComponent<Text>(smallFont, " ");
		healthUI->AddComponent<HealthObserverComponent>();
		levelScene.Add(std::move(healthUI));

		auto levelEndChecker = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
		levelEndChecker->SetName("LevelEndChecker");
		levelEndChecker->AddComponent<LevelEndCheckerComponent>();
		levelScene.Add(std::move(levelEndChecker));

		m_parser->Parse(&levelScene, "Levels/level" + std::to_string(level) + ".ppm");
	}

	void GameSettings::CreateVersusScene()
	{
		auto& levelScene = SceneManager::GetInstance().CreateScene("1");
		SceneManager::GetInstance().SetCurrentScene("1");

		const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
		const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
		const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);

		auto scoreUI = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
		scoreUI->SetName("ScoreObserver");
		scoreUI->AddComponent<Text>(smallFont, " ");
		scoreUI->AddComponent<ScoreObserverComponent>();
		levelScene.Add(std::move(scoreUI));

		auto healthUI = std::make_unique<GameObject>(glm::vec3{ 0,400,0 });
		healthUI->SetName("HealthObserver");
		healthUI->AddComponent<Text>(smallFont, " ");
		healthUI->AddComponent<HealthObserverComponent>();
		levelScene.Add(std::move(healthUI));

		m_parser->Parse(&levelScene, "Levels/Versus.ppm");
	}

	void GameSettings::CreateGameOverScene()
	{
		auto& gameOverScene = SceneManager::GetInstance().CreateScene("GameOver");
		SceneManager::GetInstance().SetCurrentScene("GameOver");

		auto bg = std::make_unique<GameObject>(0.0f, 0.0f, 0.0f);
		bg->AddComponent<SpriteComponent>("/Sprites/Menu/TitleScreen.png");

		gameOverScene.Add(std::move(bg));
	}
}
