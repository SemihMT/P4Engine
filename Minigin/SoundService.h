#pragma once
#include <condition_variable>
#include <queue>
#include <SDL_mixer.h>
#include <string>
#include <thread>
#include <unordered_map>

#include "Service.h"
#include "SoundEffect.h"

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

	//Does nothing
	class NullSoundService : public ISoundService
	{
	public:
		void PlaySound(const std::string&) override{}
		void PlayMusic(const std::string&) override{}
		void SetVolume(float) override{}
		void Mute() override{}
		void ToggleSound() override{}
	};

	//Normal sound system
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
		bool m_isMuted{ false };
		float m_volume{ 1.0f };

		void InitializeSoundLib();
		void SoundThreadFunction();
		std::jthread m_soundThread;
		std::condition_variable m_cv;
		std::mutex m_soundMtx;
		bool m_isRunning{ true };

		std::queue<std::string> m_soundQueue;
		std::queue<std::string> m_musicQueue;

		std::unordered_map<std::string,SoundEffect> m_sounds;
		std::unordered_map<std::string, Mix_Music*> m_music;

	};

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
