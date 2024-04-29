#pragma once
#include <SDL_mixer.h>
#include <string>

namespace dae
{
	class Music final
	{
	public:
		Music();
		explicit Music(const std::string& fullPath);
		~Music();


		Music(const Music&) = delete;
		Music(Music&&) = delete;
		Music& operator= (const Music&) = default;
		Music& operator= (const Music&&) = delete;

		Mix_Music* GetSoundEffect() const;

		//Loops: the number of loops to play the music for (0 means "play once and stop"). -1 means repeat indefinitely
		void Play(int loops = -1);

	private:
		Mix_Music* m_musicFile;
		std::string m_path{}; //For debug purposes, remove when done
	};
};


