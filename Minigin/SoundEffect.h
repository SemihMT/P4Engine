#pragma once
#include <SDL_mixer.h>
#include <string>

namespace dae
{
	class SoundEffect final
	{
	public:
		SoundEffect();
		explicit SoundEffect(const std::string& fullPath);
		~SoundEffect();
		

		SoundEffect(const SoundEffect&) = delete;
		SoundEffect(SoundEffect&&) = delete;
		SoundEffect& operator= (const SoundEffect&) = default;
		SoundEffect& operator= (const SoundEffect&&) = delete;

		Mix_Chunk* GetSoundEffect() const;
		//void SetChannel(int mixPlayChannel);
		void Play();

	private:
		Mix_Chunk* m_soundEffect;
		int m_channel{ -1 };
	};
}
