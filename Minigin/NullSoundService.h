#pragma once
#include "ISoundService.h"

namespace dae
{
	//Does nothing - initialize the Service Locator with this type of Service so we don't have to bother checking for nullptrs
	class NullSoundService : public ISoundService
	{
	public:
		void PlaySound(const std::string&) override {}
		void PlayMusic(const std::string&) override {}
		void SetVolume(float) override {}
		void Mute() override {}
		void ToggleSound() override {}
	};
}
