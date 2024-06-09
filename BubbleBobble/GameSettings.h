#pragma once
#include "LevelParser.h"
#include "Singleton.h"

namespace dae
{
	class GameSettings final : public Singleton<GameSettings>
	{
	public:
		enum class GameState
		{
			Singleplayer,
			Coop,
			Versus,
			Selection,
			Gameover
		};
	public:
		GameSettings(const GameSettings& other) = delete;
		GameSettings(GameSettings&& other) = delete;
		GameSettings& operator=(const GameSettings& other) = delete;
		GameSettings& operator=(GameSettings&& other) = delete;

		void Init();
		LevelParser* GetParser() const { return m_parser.get(); }
		void SetGameState(GameState type, int level);
		void SetChangeLevelFlag(int level);

		GameState GetGameState() const { return m_gameType; }
		void StartNextLevel();
		void Update();
	private:
		friend class Singleton<GameSettings>;
		GameSettings() = default;

		bool m_changeLevelFlag = false;
		int m_newLevel = 0;

		std::unique_ptr<LevelParser> m_parser;
		GameState m_gameType{ GameState::Selection };

		void CreateSingleplayerScene(int level);
		void CreateMultiplayerScene(int level);
		void CreateVersusScene();
		void CreateGameOverScene();

	};
}
