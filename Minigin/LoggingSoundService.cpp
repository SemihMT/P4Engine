#include "LoggingSoundService.h"

#include <iostream>

using namespace dae;
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
