#pragma once
#include "Command.h"
#include "ServiceLocator.h"

class ToggleSoundCommand : public Command
{
public:
	void Execute() override
	{
		ServiceLocator::getService<dae::ISoundService>("Sound")->ToggleSound();
	}
};
