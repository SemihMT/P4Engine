#include <SDL.h>
#include "InputManager.h"

#include "imgui_impl_sdl2.h"
#include "TimeManager.h"


bool dae::InputManager::ProcessInput()
{
	if(ProcessKeyboardInput() == false)
		return false;
	if (m_controllers.empty() == false)
		ProcessControllerInput();
	return true;
}

bool dae::InputManager::ProcessKeyboardInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch (e.type)
		{
		case SDL_QUIT:
		{
			return false;
		}
		break;
		case SDL_KEYDOWN:
		{
			//Get the input
			const auto pressedKey{ e.key.keysym.sym };
			//loop over all bound keyboard commands
			for (const auto& command : m_keyboardCommands)
			{
				//Check if the keyboard command should get processed in SDL_KEYDOWN
				auto keyState = command.first.second;
				if (keyState != KeyState::ButtonDown)
					continue;
				//process command
				if (command.first.first == pressedKey)
				{
					command.second->Execute();
				}
			}
		}break;
		case SDL_KEYUP:
		{
			//Get the input
			const auto pressedKey{ e.key.keysym.sym };
			//loop over all bound keyboard commands
			for (const auto& command : m_keyboardCommands)
			{
				//Check if the keyboard command should get processed in SDL_KEYDOWN
				auto keyState = command.first.second;
				if (keyState != KeyState::ButtonUp)
					continue;
				//process command
				if (command.first.first == pressedKey)
				{
					command.second->Execute();
				}
			}
		}break;

		default:
			return true;
		}

	}

	const auto pressedKeys = SDL_GetKeyboardState(nullptr);
	for (const auto& command : m_keyboardCommands)
	{
		if (pressedKeys[SDL_GetScancodeFromKey(command.first.first)])
		{
			command.second->Execute();
		}

	}
	return true;
}

bool dae::InputManager::ProcessControllerInput()
{
	for(const auto& controller : m_controllers)
	{
		controller->Update();
		for(const auto& command : m_consoleCommands)
		{
			//Check if this command was bound to this controller
			if((int)command.first.first != controller->GetControllerIndex())
				continue;
			if (controller->IsPressed(command.first.second))
				command.second->Execute();

			
		}

	}
	return true;
}

unsigned dae::InputManager::AddController()
{
	// Return 999 if we've reached the limit of 4 controllers
	if (m_controllers.size() >= 4)
		return 999;

	unsigned int controllerIdx = m_controllerCounter;
	++m_controllerCounter;

	m_controllers.emplace_back(std::make_unique<XInputController>(controllerIdx));

	return controllerIdx;

}

void dae::InputManager::BindControllerCommand(ControllerKey key, std::unique_ptr<Command> command)
{
	m_consoleCommands[key] = std::move(command);
}

void dae::InputManager::BindControllerCommand(Controller controllerId, XInputController::Button button,
	std::unique_ptr<Command> command)
{
	const ControllerKey controllerKey = std::make_pair(controllerId, button);
	m_consoleCommands[controllerKey] = std::move(command);
}


void dae::InputManager::BindKeyboardCommand(SDL_KeyCode keyCode, std::unique_ptr<Command> command, KeyState executionState)
{
	const KeyboardKey key = std::pair(keyCode, executionState);
	m_keyboardCommands[key] = std::move(command);
}

bool dae::InputManager::IsDown(Controller idx, XInputController::Button button) const
{
	return m_controllers[static_cast<int>(idx)]->IsDown(button);
}

bool dae::InputManager::IsUp(Controller idx, XInputController::Button button) const
{
	return m_controllers[static_cast<int>(idx)]->IsUp(button);
}

bool dae::InputManager::IsPressed(Controller idx, XInputController::Button button) const
{
	return m_controllers[static_cast<int>(idx)]->IsPressed(button);
}

const glm::vec2& dae::InputManager::GetLeftThumbDir(Controller idx) const
{
	return m_controllers[static_cast<int>(idx)]->GetLeftThumbDir();
}

const glm::vec2& dae::InputManager::GetRightThumbDir(Controller idx) const
{
	return m_controllers[static_cast<int>(idx)]->GetRightThumbDir();
}
