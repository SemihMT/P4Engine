#include "GameSettings.h"
namespace dae
{
	void GameSettings::Init()
	{
		m_parser = std::make_unique<LevelParser>();
	}
}
