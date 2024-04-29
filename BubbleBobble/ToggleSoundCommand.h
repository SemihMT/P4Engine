#pragma once
#include "Command.h"
#include "ServiceLocator.h"
namespace dae
{
	class ToggleSoundCommand : public Command
	{
	public:
		void Execute() override
		{
			ServiceLocator::GetInstance().GetService<ISoundService>("Sound")->ToggleSound();
		}
	};
}
