#include "SoundService.h"
#include <iostream>
#include "ResourceManager.h"

using namespace dae;
void SoundService::InitializeSoundLib()
{

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
		printf("SDL Mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	//Mix_AllocateChannels(16);
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);

	printf("Mixer has been initialized!\n");
}

SoundService::SoundService()
{
	InitializeSoundLib();
	m_soundThread = std::jthread{ &SoundService::SoundThreadFunction,this };
	printf("Normal SoundService Initialized!\n");
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
				m_sounds.insert(std::make_pair(sound, std::make_unique<SoundEffect>(sound)));
			}
 			m_sounds[sound]->Play();
		}

		if (!m_musicQueue.empty())
		{
			auto music = m_musicQueue.front();
			m_musicQueue.pop();

			//Play the music if it's cached
			if (!m_music.contains(music))
			{
				m_music.insert(std::make_pair(music, std::make_unique<Music>(music)));
			}
			m_music[music]->Play();
		}
	}
}



LoggingSoundService::LoggingSoundService() : m_realSoundService{ std::make_unique<SoundService>() }
{
	printf("Logging SoundService Initialized!\n");
}

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
