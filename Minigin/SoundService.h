#pragma once
#include <memory>
#include <string>
#include "ISoundService.h"

namespace dae
{
	//Normal sound system - PIMPL'd away the actual implementation of the interface
	class SoundService final: public ISoundService
	{
	public:
		SoundService();
		~SoundService() override;

		SoundService(const SoundService& other) = delete;
		SoundService(SoundService&& other) = delete;
		SoundService& operator=(const SoundService& other) = delete;
		SoundService& operator=(SoundService&& other) = delete;

		void PlaySound(const std::string& sound) override;
		void PlayMusic(const std::string& music) override;
		void SetVolume(float volume) override;
		void Mute() override;
		void ToggleSound() override;
	private:

		class SoundServiceImpl;
		std::unique_ptr<SoundServiceImpl> m_pImpl{};

	};

	
}
