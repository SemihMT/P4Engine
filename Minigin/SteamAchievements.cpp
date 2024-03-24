#include "SteamAchievements.h"

void dae::SteamAchievements::Init()
{
	m_steamAchievements = std::make_unique<CSteamAchievements>(m_Achievements,4);
}
