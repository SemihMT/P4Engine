#include "SoundService.h"
#include <iostream>
#include <mutex>
#include <queue>
#include <unordered_map>

#include "Music.h"
#include "ResourceManager.h"
#include "SoundEffect.h"

using namespace dae;
class SoundService::SoundServiceImpl final
{
public:
	SoundServiceImpl()
	{
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
			printf("SDL Mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
		//Mix_AllocateChannels(16);
		Mix_Volume(-1, MIX_MAX_VOLUME / 2);

		printf("Mixer has been initialized!\n");

		m_soundThread = std::jthread{ &SoundServiceImpl::SoundThreadFunction, this };
	}
	virtual ~SoundServiceImpl()
	{
		m_isRunning = false;
		m_cv.notify_all(); //notify the thread to stop waiting
		if (m_soundThread.joinable())
			m_soundThread.join();

		m_soundsMap.clear();
		m_musicMap.clear();

		Mix_CloseAudio();
		Mix_Quit();
	}

	SoundServiceImpl(const SoundServiceImpl& other) = delete;
	SoundServiceImpl(SoundServiceImpl&& other) = delete;
	SoundServiceImpl& operator=(const SoundServiceImpl& other) = delete;
	SoundServiceImpl& operator=(SoundServiceImpl&& other) = delete;

	void PlaySound(const std::string& sound)
	{
		std::lock_guard<std::mutex> lock(m_soundMtx);
		//add the requested sound to the queue
		m_soundQueue.push(dae::ResourceManager::GetInstance().GetDataPath() + "Sounds/FX/" + sound);
		m_cv.notify_one();
	}
	void PlayMusic(const std::string& music)
	{
		std::lock_guard<std::mutex> lock(m_soundMtx);
		m_musicQueue.push(dae::ResourceManager::GetInstance().GetDataPath() + "Sounds/" + music);
		m_cv.notify_one();
	}
	void SetVolume(float volume)
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
	void Mute()
	{
		m_isMuted = true;
		SetVolume(0.0f);
	}
	void ToggleSound()
	{
		if (m_isMuted)
			SetVolume(m_volume);
		else
			Mute();
	}

private:
	bool m_isMuted{ false };
	float m_volume{ 1.0f };

	void SoundThreadFunction()
	{
		while (m_isRunning)
		{
			std::unique_lock<std::mutex> lock(m_soundMtx);
			m_cv.wait(lock, [this] {return !m_soundQueue.empty() || !m_musicQueue.empty() || !m_isRunning; });
			if (!m_isRunning) break;


			std::string sound;
			std::string music;

			if (!m_soundQueue.empty())
			{
				sound = m_soundQueue.front();
				m_soundQueue.pop();
			}
			if (!m_musicQueue.empty())
			{
				music = m_musicQueue.front();
				m_musicQueue.pop();
			}
			lock.unlock(); // release the lock

			//m_soundQueue = std::queue<std::string>
			if (!sound.empty())
			{
				//Play the sound if it's cached
				if (!m_soundsMap.contains(sound))
				{
					m_soundsMap.insert(std::make_pair(sound, std::make_unique<SoundEffect>(sound)));
				}
				m_soundsMap[sound]->Play();
			}
			//m_musicQueue = std::queue<std::string>
			if (!music.empty())
			{
				//Play the music if it's cached
				if (!m_musicMap.contains(music))
				{
					m_musicMap.insert(std::make_pair(music, std::make_unique<Music>(music)));
				}
				m_musicMap[music]->Play();
			}
		}
	}
	std::jthread m_soundThread{};
	std::condition_variable m_cv{};
	std::mutex m_soundMtx{};
	bool m_isRunning{ true };

	std::queue<std::string> m_soundQueue{};
	std::queue<std::string> m_musicQueue{};

	std::unordered_map<std::string, std::unique_ptr<SoundEffect>> m_soundsMap{};
	std::unordered_map<std::string, std::unique_ptr<Music>> m_musicMap{};
};


SoundService::SoundService() : m_pImpl{ std::make_unique<SoundServiceImpl>() }
{
}

SoundService::~SoundService() = default;
void SoundService::PlaySound(const std::string& sound)
{
	m_pImpl->PlaySound(sound);
}

void SoundService::PlayMusic(const std::string& music)
{
	m_pImpl->PlayMusic(music);
}

void SoundService::SetVolume(float volume)
{
	m_pImpl->SetVolume(volume);
}

void SoundService::Mute()
{
	m_pImpl->Mute();
}

void SoundService::ToggleSound()
{
	m_pImpl->ToggleSound();
}

