#include "PlayerEventHandlerComponent.h"
#include <iostream>

#include "GameObject.h"
#include "HitState.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "MoveCommand.h"
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ShootCommand.h"
#include "SpriteComponent.h"
#include "StateComponent.h"

dae::PlayerEventHandlerComponent::PlayerEventHandlerComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::PlayerEventHandlerComponent::OnNotify(Event event, const EventData& data)
{
	switch (event)
	{
	case Event::Player_Spawn:
		std::cout << "\033[32m" << "Player Spawn Event;" << "\033[0m" << "\n";
		BindAllControls(data.Get<int>("PlayerNumber"));
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
		{
			GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<HitState>(GetOwner(), GetOwner()->GetComponent<PlayerComponent>()->GetPlayerNumber()));
			UnbindAllControls(data.Get<int>("PlayerNumber"));
		}
		break;
	case Event::Player_ShootBubble:
		std::cout << "\033[32m" << "Player Shoot Event;" << "\033[0m" << "\n";
		break;
	case Event::Player_Jump:
		std::cout << "\033[32m" << "Player Jump Event;" << "\033[0m" << "\n";
		break;
	case Event::Player_Fall:
		if (data.Get<GameObject*>("Player")->GetComponent<PlayerComponent>()->GetPlayerNumber() == 1)
		{
			InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 25.0f));
			InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 25.0f));
			InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 25.0f));
			InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 25.0f));
		}
		else
		{
			InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 25.0f));
			InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 25.0f));
		}
		break;
	case Event::Player_Move:
		if (data.Get<GameObject*>("Player")->GetComponent<PlayerComponent>()->GetPlayerNumber() == 1)
		{
			InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
			InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
			InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
			InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		}
		else
		{
			InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
			InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		}

		break;
	case Event::Bubble_PopEnemy:
	{
		const auto poppedEnemy = data.Get<GameObject*>("PoppedEnemy");
		auto poppedEnemyPos = poppedEnemy->GetTransform()->GetWorldPosition();
		const auto poppedEnemyType = poppedEnemy->GetName();
		SceneManager::GetInstance().GetCurrentScene()->Remove(poppedEnemy);
		if (poppedEnemyType == "ZenChanBubble")
		{
			auto watermelonItem = std::make_unique<GameObject>(poppedEnemyPos);
			watermelonItem->SetName("Watermelon");
			watermelonItem->AddComponent<SpriteComponent>("/Sprites/Items/Watermelon.png", glm::ivec2{ 16 }, 0, 0, glm::ivec2{ 32 });
			watermelonItem->AddComponent<ColliderComponent>(32, ColliderType::Trigger);
			SceneManager::GetInstance().GetCurrentScene()->Add(std::move(watermelonItem));
		}
		else
		{
			auto friesItem = std::make_unique<GameObject>(poppedEnemyPos);
			friesItem->SetName("Fries");
			friesItem->AddComponent<SpriteComponent>("/Sprites/Items/Fries.png", glm::ivec2{ 16 }, 0, 0, glm::ivec2{ 32 });
			friesItem->AddComponent<ColliderComponent>(32, ColliderType::Trigger);

			//friesItem->AddComponent<FriesComponent>();
			SceneManager::GetInstance().GetCurrentScene()->Add(std::move(friesItem));

		}
	}
	break;

	case Event::Item_Collected:
		auto collectedItem = data.Get<GameObject*>("Item");
		auto player = data.Get<GameObject*>("Player");

		//std::cout << "Collected: " << collectedItem->GetName() << " by " << player->GetName() << " " << player->GetComponent<PlayerComponent>()->GetPlayerNumber() << "\n";

		if (collectedItem->GetName() == "Watermelon")
			player->GetComponent<ScoreComponent>()->AddToScore(100);
		else
			player->GetComponent<ScoreComponent>()->AddToScore(200);
		SceneManager::GetInstance().GetCurrentScene()->Remove(collectedItem);

		break;

	}
}

void dae::PlayerEventHandlerComponent::Update()
{

}

void dae::PlayerEventHandlerComponent::UnbindAllControls(int playerNumber)
{
	/*InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<GameObjectCommand>(GetOwner()));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<GameObjectCommand>(GetOwner()));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
	InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);*/


	if (playerNumber == 1)
	{
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<GameObjectCommand>(GetOwner()));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<GameObjectCommand>(GetOwner()));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
		InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);

		//InputManager::GetInstance().AddController();
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<GameObjectCommand>(GetOwner()));
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<GameObjectCommand>(GetOwner()));
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::A, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::B, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
	}
	else
	{
		//InputManager::GetInstance().AddController();
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_LEFT, std::make_unique<GameObjectCommand>(GetOwner()));
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_RIGHT, std::make_unique<GameObjectCommand>(GetOwner()));
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::A, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::B, std::make_unique<GameObjectCommand>(GetOwner()), KeyState::ButtonUp);
	}
}

void dae::PlayerEventHandlerComponent::BindAllControls(int playerNumber)
{
	if (playerNumber == 1)
	{
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<JumpCommand>(GetOwner()), KeyState::ButtonUp);
		InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<ShootCommand>(GetOwner()), KeyState::ButtonUp);

		//InputManager::GetInstance().AddController();
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::A, std::make_unique<JumpCommand>(GetOwner()), KeyState::ButtonUp);
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::B, std::make_unique<ShootCommand>(GetOwner()), KeyState::ButtonUp);
	}
	else
	{
		//InputManager::GetInstance().AddController();
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ -1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(GetOwner(), glm::vec3{ 1.f, 0.f, 0.f }, 64.0f));
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::A, std::make_unique<JumpCommand>(GetOwner()), KeyState::ButtonUp);
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::B, std::make_unique<ShootCommand>(GetOwner()), KeyState::ButtonUp);
	}
}
