#include "SoundEffect.h"

#include <stdexcept>

dae::SoundEffect::SoundEffect() : m_soundEffect{nullptr}
{
}

dae::SoundEffect::SoundEffect(const std::string& fullPath): m_soundEffect{nullptr}, m_path{fullPath}
{
	m_soundEffect = Mix_LoadWAV(fullPath.c_str());
	if (m_soundEffect == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load WAV file: ") + SDL_GetError());
	}
}

dae::SoundEffect::~SoundEffect()
{
	//This code throws an "access violation exception"
	//VLD does not register a memory leak when not calling these functions to free the Mix_Chunk
	//Does it get freed somewhere else?

	/*if (Mix_Playing(m_channel) > 0)
		Mix_HaltChannel(m_channel);*/
	
	Mix_FreeChunk(m_soundEffect);
	m_soundEffect = nullptr;
	printf("Destroyed SoundEffect [%s]", m_path.c_str());
}

Mix_Chunk* dae::SoundEffect::GetSoundEffect() const
{
	return m_soundEffect;
}

//void dae::SoundEffect::SetChannel(int mixPlayChannel)
//{
//	m_channel = mixPlayChannel;
//}

void dae::SoundEffect::Play()
{
	m_channel = Mix_PlayChannel(-1, m_soundEffect,0);
}
