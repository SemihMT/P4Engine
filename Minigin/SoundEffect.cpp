#include "SoundEffect.h"

#include <stdexcept>

dae::SoundEffect::SoundEffect() : m_soundEffect{nullptr}
{
}

dae::SoundEffect::SoundEffect(const std::string& fullPath): m_soundEffect{nullptr}
{
	m_soundEffect = Mix_LoadWAV(fullPath.c_str());
	if (m_soundEffect == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load WAV file: ") + SDL_GetError());
	}
}

dae::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_soundEffect);
}

Mix_Chunk* dae::SoundEffect::GetSoundEffect() const
{
	return m_soundEffect;
}
