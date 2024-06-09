#include "GameSettings.h"

#include "HealthObserverComponent.h"
#include "HighScoreDisplayComponent.h"
#include "IdentifierComponent.h"
#include "LevelEndCheckerComponent.h"
#include "SceneManager.h"
#include "ScoreObserverComponent.h"
#include "SelectorComponent.h"
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

	void GameSettings::SaveScore(int score)
	{
		m_score += score;
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
		const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);

		auto& gameOverScene = SceneManager::GetInstance().CreateScene("GameOver");
		SceneManager::GetInstance().SetCurrentScene("GameOver");

		auto bg = std::make_unique<GameObject>(0.0f, 0.0f, 0.0f);
		bg->AddComponent<SpriteComponent>("/Sprites/Menu/Background.png", glm::ivec2{ 256,224 }, 0, 0, glm::ivec2{ 512,448 });

		auto title = std::make_unique<GameObject>(180.0f, 50.0f, 0.0f);
		title->AddComponent<Text>(smallFont, "High scores:");

		auto highscoreDisplay = std::make_unique<GameObject>(180.0f, 150.0f, 0.0f);
		highscoreDisplay->AddComponent<Text>(smallFont," ");
		highscoreDisplay->AddComponent<HighScoreDisplayComponent>();

		auto identifier = std::make_unique<GameObject>(180.0f,250.0f,0.0f);
		identifier->AddComponent<Text>(smallFont, " ");
		identifier->AddComponent<IdentifierComponent>();


		gameOverScene.Add(std::move(bg));
		gameOverScene.Add(std::move(title));
		gameOverScene.Add(std::move(highscoreDisplay));
		gameOverScene.Add(std::move(identifier));
	}
}
