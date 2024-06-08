#pragma once
#include "LevelParser.h"
#include "Singleton.h"

namespace dae
{
	class GameSettings final : public Singleton<GameSettings>
	{
	public:
		enum class GameType
		{
			Singleplayer,
			Coop,
			Versus
		};
	public:
		GameSettings(const GameSettings& other) = delete;
		GameSettings(GameSettings&& other) = delete;
		GameSettings& operator=(const GameSettings& other) = delete;
		GameSettings& operator=(GameSettings&& other) = delete;

		void Init();
		LevelParser* GetParser() const { return m_parser.get(); }
	private:
		friend class Singleton<GameSettings>;
		GameSettings() = default;

		std::unique_ptr<LevelParser> m_parser;

	};
}
