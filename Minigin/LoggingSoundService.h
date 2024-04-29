#pragma once
#include "SoundService.h"

namespace dae
{
	//Decorator pattern
	class LoggingSoundService final : public ISoundService
	{
	public:
		LoggingSoundService();
		~LoggingSoundService() override = default;

		LoggingSoundService(const LoggingSoundService& other) = delete;
		LoggingSoundService(LoggingSoundService&& other) = delete;
		LoggingSoundService& operator=(const LoggingSoundService& other) = delete;
		LoggingSoundService& operator=(LoggingSoundService&& other) = delete;

		void PlaySound(const std::string& sound) override;

		void PlayMusic(const std::string& music) override;

		void SetVolume(float volume) override;

		void Mute() override;

		void ToggleSound() override;

	private:
		std::unique_ptr<SoundService> m_realSoundService;

	};
}

