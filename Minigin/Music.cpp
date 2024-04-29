#include "Music.h"

dae::Music::Music() : m_musicFile{nullptr}
{
}

dae::Music::Music(const std::string& fullPath) : m_musicFile{nullptr}, m_path{ fullPath }
{
	m_musicFile =  Mix_LoadMUS(fullPath.c_str());
	if (m_musicFile == nullptr)
	{
		printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
	}
}

dae::Music::~Music()
{
	Mix_FreeMusic(m_musicFile);
	m_musicFile = nullptr;

	printf("Destroyed Music [%s]", m_path.c_str());

}

Mix_Music* dae::Music::GetSoundEffect() const
{
	return m_musicFile;
}

void dae::Music::Play(int loops)
{
	if(Mix_PlayMusic(m_musicFile, loops) == -1 )
		printf("Failed to play music. SDL_Mixer error: %s\n", Mix_GetError());
}
