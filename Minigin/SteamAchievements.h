#pragma once
#include <memory>

#include "Singleton.h"
#include "StatsAndAchievements.h"

namespace dae
{
	class SteamAchievements : public Singleton<SteamAchievements>
	{
	public:
		void Init();
		CSteamAchievements* GetSteamAchievements() const { return m_steamAchievements.get(); }

	private:
		friend class Singleton<SteamAchievements>;
		SteamAchievements() = default;
		std::unique_ptr<CSteamAchievements> m_steamAchievements{ nullptr };

		// Achievement array which will hold data about the achievements and their state
		Achievement_t m_Achievements[4] =
		{
			_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
			_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
			_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
			_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
		};

	};
}
