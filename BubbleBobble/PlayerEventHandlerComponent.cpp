#include "PlayerEventHandlerComponent.h"
#include <iostream>

#include "GameObject.h"
#include "HitState.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "MoveCommand.h"
#include "PlayerComponent.h"
#include "ShootCommand.h"
#include "StateComponent.h"

dae::PlayerEventHandlerComponent::PlayerEventHandlerComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::PlayerEventHandlerComponent::OnNotify(Event event, const EventData& data)
{
	(void)data;
	switch (event)
	{
	case Event::Player_Spawn:
		std::cout << "\033[32m" << "Player Spawn Event;" << "\033[0m" << "\n";
		BindAllControls();
		break;
	case Event::Player_Idle:
		std::cout << "\033[32m" << "Player Idle Event;" << "\033[0m" << "\n";
		break;
	case Event::Player_Death:
		std::cout << "\033[32m" << "Player Death Event;" << "\033[0m" << "\n";
		//Go to end screen to save high score
		break;
	case Event::Player_Respawn:
		std::cout << "\033[32m" << "Player Respawn Event;" << "\033[0m" << "\n";
		break;
	case Event::Player_Damaged:
		std::cout << "\033[32m" << "Player Damaged Event;" << "\033[0m" << "\n";
		GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<HitState>(GetOwner()));
		UnbindAllControls();
		break;
	case Event::Player_ShootBubble:
		std::cout << "\033[32m" << "Player Shoot Event;" << "\033[0m" << "\n";
		break;
	case Event::Player_Jump:
		std::cout << "\033[32m" << "Player Jump Event;" << "\033[0m" << "\n";
		break;
	case Event::Player_Fall:
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 25.0f));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 25.0f));
		break;
	case Event::Player_Move:
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		break;

	}
}

void dae::PlayerEventHandlerComponent::Update()
{

}

void dae::PlayerEventHandlerComponent::UnbindAllControls()
{
	InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<GameObjectCommand>(GetOwner()));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<GameObjectCommand>(GetOwner()));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
	InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
}

void dae::PlayerEventHandlerComponent::BindAllControls()
{
	InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<JumpCommand>(GetOwner()), KeyState::ButtonUp);
	InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<ShootCommand>(GetOwner()), KeyState::ButtonUp);
}
