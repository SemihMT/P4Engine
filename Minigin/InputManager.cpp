#include <SDL.h>
#include "InputManager.h"

#include "imgui_impl_sdl2.h"
#include "TimeManager.h"


bool dae::InputManager::ProcessInput()
{
	if (ProcessKeyboardInput() == false)
		return false;
	if (m_controllers.empty() == false)
		ProcessControllerInput();
	return true;
}

bool dae::InputManager::ProcessKeyboardInput()
{
		// Get the current state of the keyboard
	const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
	// Copy the current state to m_previousKeyState
	std::copy(currentKeyState, currentKeyState + SDL_NUM_SCANCODES, m_previousKeyState);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
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
		if (pressedKeys[SDL_GetScancodeFromKey(command.first.first)] && command.first.second == KeyState::Hold)
		{
			command.second->Execute();
		}

	}



	return true;
}

bool dae::InputManager::ProcessControllerInput()
{
	for (const auto& controller : m_controllers)
	{
		if (controller->CheckForConnection())
			controller->Update();
		else
			continue;

		for (const auto& command : m_consoleCommands)
		{
			//Stored controller enum
			Controller ctrl{ command.first.first.first };
			//Check if this command was bound to this controller
			if (static_cast<int>(ctrl) != controller->GetControllerIndex())
				continue;

			//The button this command was bound to
			const XInputController::Button btn{ command.first.first.second };
			if (command.first.second == KeyState::ButtonDown)
			{
				if (controller->IsDown(btn))
					command.second->Execute();
			}
			if (command.first.second == KeyState::ButtonUp)
			{
				if (controller->IsUp(btn))
					command.second->Execute();
			}
			if (command.first.second == KeyState::Hold)
			{
				if (controller->IsPressed(btn))
					command.second->Execute();
			}


			if (controller->GetLeftThumbDir() != glm::vec2{ 0.0f,0.0f } && btn == XInputController::Button::LEFT_THUMB)
			{
				command.second->Execute();
			}

		}

	}
	return true;
}

unsigned dae::InputManager::AddController()
{
	// Return 999 if we've reached the limit of 4 controllers
	if (m_controllers.size() >= 2)
		return 999;

	unsigned int controllerIdx = m_controllerCounter;
	++m_controllerCounter;

	m_controllers.emplace_back(std::make_unique<XInputController>(controllerIdx));

	return controllerIdx;

}


void dae::InputManager::BindControllerCommand(ControllerKey key, std::unique_ptr<Command> command, KeyState executionState)
{
	const ControllerKeyAndState controllerKeyState = std::make_pair(key, executionState);
	m_consoleCommands[controllerKeyState] = std::move(command);
}

void dae::InputManager::BindControllerCommand(Controller controllerId, XInputController::Button button,
	std::unique_ptr<Command> command, KeyState executionState)
{
	const ControllerKey controllerKey = std::make_pair(controllerId, button);
	const ControllerKeyAndState controllerKeyState = std::make_pair(controllerKey, executionState);
	m_consoleCommands[controllerKeyState] = std::move(command);
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

bool dae::InputManager::IsDown(SDL_KeyCode key) const
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
	return currentKeyState[SDL_GetScancodeFromKey(key)] != 0;
}

bool dae::InputManager::IsUp(SDL_KeyCode key) const
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
	const Uint8 scancode = static_cast<Uint8>(SDL_GetScancodeFromKey(key));
	return !currentKeyState[scancode] && m_previousKeyState[scancode];
}

bool dae::InputManager::IsPressed(SDL_KeyCode key) const
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
	const Uint8 scancode = static_cast<Uint8>(SDL_GetScancodeFromKey(key));
	return currentKeyState[scancode] && !m_previousKeyState[scancode];
}



const glm::vec2 dae::InputManager::GetLeftThumbDir(Controller idx) const
{
	return m_controllers[static_cast<int>(idx)]->GetLeftThumbDir();
}

const glm::vec2 dae::InputManager::GetRightThumbDir(Controller idx) const
{
	return m_controllers[static_cast<int>(idx)]->GetRightThumbDir();
}
