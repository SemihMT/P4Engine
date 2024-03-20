#pragma once
#include <map>

#include "Singleton.h"
#include <memory>
#include <vector>

#include "Command.h"
#include "XInputController.h"

namespace dae
{
	enum class Controller : unsigned int
	{
		One = 0,
		Two = 1,
		Three = 2,
		Four = 3
	};

	enum class KeyState
	{
		ButtonDown,
		ButtonUp,
		Hold
	};
	//<Controller IDX, button on controller>
	using ControllerKey = std::pair<Controller, XInputController::Button>;
	using KeyboardKey = std::pair<SDL_KeyCode, KeyState>;
	
	class InputManager final : public Singleton<InputManager>
	{
		
		//<key on a given controller, command to execute when that key gets pressed>
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		//<Key on the keyboard, command that gets executed when that key gets pressed>
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;
	
	public:
		
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();
		bool ProcessKeyboardInput();
		bool ProcessControllerInput();
		//Adds a new controller and stores it in m_controllers
		unsigned int AddController();
		//Binding a command to a controller's key
		void BindControllerCommand(ControllerKey key, std::unique_ptr<Command> command);
		void BindControllerCommand(Controller controllerId, XInputController::Button button, std::unique_ptr<Command> command);
		//Binding a command to keyboard input + the state during which the command should get executed
		void BindKeyboardCommand(SDL_KeyCode keyCode, std::unique_ptr<Command> command, KeyState executionState = KeyState::ButtonDown);

		//Keystate getters
		bool IsDown(Controller idx, XInputController::Button button) const;
		bool IsUp(Controller idx, XInputController::Button button) const;
		bool IsPressed(Controller idx, XInputController::Button button) const;
		const glm::vec2 GetLeftThumbDir(Controller idx) const;
		const glm::vec2 GetRightThumbDir(Controller idx) const;

	private:
		friend class Singleton<InputManager>;
		InputManager() = default;

		unsigned int m_controllerCounter{ 0 };
		std::vector<std::unique_ptr<XInputController>> m_controllers{};
		ControllerCommandsMap m_consoleCommands{};
		KeyboardCommandsMap m_keyboardCommands{};

	};

}
