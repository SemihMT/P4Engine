#pragma once
#include <string>

#include "Service.h"

namespace dae
{
	//Interface for sound systems
	class ISoundService : public Service
	{
	public:
		virtual ~ISoundService() = default;

		virtual void PlaySound(const std::string& sound) = 0;
		virtual void PlayMusic(const std::string& music) = 0;
		virtual void SetVolume(float volume) = 0;
		virtual void Mute() = 0;
		virtual void ToggleSound() = 0;
	};
}
