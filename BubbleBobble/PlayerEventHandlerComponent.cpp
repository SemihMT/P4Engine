#include "PlayerEventHandlerComponent.h"
#include <iostream>

#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "PlayerComponent.h"

dae::PlayerEventHandlerComponent::PlayerEventHandlerComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::PlayerEventHandlerComponent::OnNotify(Event event, const EventData& data)
{
	(void)data;
	//Events will come from states?
	switch (event)
	{
	case Event::Player_Spawn:
		std::cout << "Player notified from Spawn state;\n";
		//PlayerInit();
		break;
	case Event::Player_Idle:
		std::cout << "Player notified from the Idle state\n";
		break;
	case Event::Player_Death:
		break;
	case Event::Player_Respawn:
		break;
	case Event::Player_Damaged:
		//PlayerDamage();
		break;
	case Event::Player_ShootBubble:
		//SetState shoot
		break;
	case Event::Player_Jump:

		break;
	case Event::Player_Fall:
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 25.0f));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 25.0f));
		break;
	case Event::Player_Move:
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		break;

	case Event::Bubble_HitEnemy:
		break;
	case Event::Bubble_PopEnemy:
		break;
	case Event::Bubble_PopNoEnemy:
		break;
	case Event::Item_Collected:
		break;

	}
}
