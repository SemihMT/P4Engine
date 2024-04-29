#include "SoundService.h"

#include <iostream>

#include "ResourceManager.h"


using namespace dae;
SoundService::SoundService()
{
	InitializeSoundLib();

	m_soundThread = std::jthread{ &SoundService::SoundThreadFunction,this };
}

SoundService::~SoundService()
{
	m_isRunning = false;
	m_cv.notify_all(); //notify the thread to stop waiting
	if (m_soundThread.joinable())
		m_soundThread.join();

	m_sounds.clear();
	m_music.clear();

	Mix_CloseAudio();
	Mix_Quit();
}

void SoundService::PlaySound(const std::string& sound)
{
	//add the requested sound to the queue
	m_soundQueue.push(dae::ResourceManager::GetInstance().GetDataPath() + "Sounds/FX/" + sound);
	m_cv.notify_one();
}

void SoundService::PlayMusic(const std::string& music)
{
	m_musicQueue.push(dae::ResourceManager::GetInstance().GetDataPath() + "Sounds/" + music);
	m_cv.notify_one();
}

void SoundService::SetVolume(float volume)
{
	if (volume < 0.0f)
		return;

	float newVol{ MIX_MAX_VOLUME };
	newVol *= volume;


	if (static_cast<int>(newVol) == 0)
	{
		m_isMuted = true;
	}
	else
	{
		m_isMuted = false;
		m_volume = volume;
	}

	// -1 means that we set the volume for all available channels
	Mix_Volume(-1, static_cast<int>(newVol));
	Mix_VolumeMusic(static_cast<int>(newVol));
}

void SoundService::Mute()
{
	m_isMuted = true;
	SetVolume(0.0f);
}

void SoundService::ToggleSound()
{
	if (m_isMuted)
		SetVolume(m_volume);
	else
		Mute();

}

void SoundService::InitializeSoundLib()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
		printf("SDL Mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_AllocateChannels(16);
	Mix_Volume(-1, MIX_MAX_VOLUME);
}

void SoundService::SoundThreadFunction()
{

	while (m_isRunning)
	{
		std::unique_lock<std::mutex> lock(m_soundMtx);

		m_cv.wait(lock, [this] {return !m_soundQueue.empty() || !m_musicQueue.empty() || !m_isRunning; });
		if (!m_isRunning) break;


		if (!m_soundQueue.empty())
		{

			auto sound = m_soundQueue.front();
			m_soundQueue.pop();

			//Play the sound if it's cached
			if (!m_sounds.contains(sound))
			{
				const SoundEffect soundEffect{ sound };
				m_sounds[sound] = soundEffect;
			}
 			m_sounds[sound].Play();
		}

		if (!m_musicQueue.empty())
		{
			auto music = m_musicQueue.front();
			m_musicQueue.pop();

			//Play the music if it's cached
			if (!m_music.contains(music))
			{
				Mix_Music* m{ Mix_LoadMUS(music.c_str()) };
				if (m == nullptr)
				{
					printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
				}
				else
					m_music[music] = m;
			}
			Mix_PlayMusic(m_music[music], -1);
		}
	}
}



LoggingSoundService::LoggingSoundService() : m_realSoundService{ std::make_unique<SoundService>() }
{}

void LoggingSoundService::PlaySound(const std::string& sound)
{
	m_realSoundService->PlaySound(sound);
	std::cout << "Playing sound effect [" << sound << "]\n";
}

void LoggingSoundService::PlayMusic(const std::string& music)
{
	m_realSoundService->PlayMusic(music);
	std::cout << "Playing music [" << music << "]\n";
}

void LoggingSoundService::SetVolume(float volume)
{
	m_realSoundService->SetVolume(volume);
	std::cout << "Set volume to [" << volume << "]\n";
}

void LoggingSoundService::Mute()
{
	m_realSoundService->Mute();
	std::cout << "Muted the sound service\n";
}

void LoggingSoundService::ToggleSound()
{
	m_realSoundService->ToggleSound();
	std::cout << "Toggling sound on/off\n";
}
