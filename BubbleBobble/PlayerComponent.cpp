#include "PlayerComponent.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "MoveCommand.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ShootBubble.h"
#include "ShootCommand.h"
#include "SpawnState.h"
#include "StateComponent.h"
#include "ScoreObserverComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* owner, int playerNumber, const glm::vec3& direction) :
	BaseComponent(owner),
	m_transform{ owner->GetTransform() },
	m_playerNumber{ playerNumber },
	m_spawnDirection{ direction }
{

	owner->SetName("Player");

	if (m_playerNumber == 1)
		m_playerSpriteSheet = "Sprites/Characters/Player/BobSpriteSheet.png";
	if (m_playerNumber == 2)
		m_playerSpriteSheet = "Sprites/Characters/Player/BubSpriteSheet.png";

	owner->AddComponent<AnimationComponent>(m_playerSpriteSheet);
	owner->GetComponent<AnimationComponent>()->SetDestinationSize({ m_dstSize,m_dstSize });
	int row = 0;
	int numFrames = 4;
	const AnimationData walkAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Walk", walkAnimation);

	row = 0;
	numFrames = 2;
	const AnimationData idleAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Idle", idleAnimation);

	row = 1;
	numFrames = 2;
	const AnimationData jumpUpAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("JumpUp", jumpUpAnimation);
	row = 2;
	numFrames = 2;
	const AnimationData fallDownAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("FallDown", fallDownAnimation);

	row = 3;
	numFrames = 1;
	const AnimationData shootAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Shoot", shootAnimation);

	row = 7;
	numFrames = 6;
	const AnimationData deathAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Death", deathAnimation);

	m_spawnPosition = m_transform->GetLocalPosition() * glm::vec3{ static_cast<float>(m_srcSize) };

	auto observer = owner->AddComponent<PlayerEventHandlerComponent>();
	owner->AddComponent<StateComponent>();
	owner->GetComponent<StateComponent>()->SetState(std::make_unique<SpawnState>(owner, m_spawnPosition, m_spawnDirection, m_playerNumber));
	owner->AddComponent<ColliderComponent>(m_dstSize, ColliderType::Trigger)->AddObserver(observer);
	owner->AddComponent<RigidBodyComponent>();


	auto scoreObserver = SceneManager::GetInstance().GetCurrentScene()->GetGameObject("ScoreObserver");
	owner->AddComponent<ScoreComponent>(0)->AddObserver(scoreObserver->GetComponent<ScoreObserverComponent>());


	for (int i{}; i < 16; ++i)
	{
		auto bubble = std::make_unique<GameObject>();
		bubble->AddComponent<BubbleComponent>(m_playerSpriteSheet);
		m_bubbles[i] = bubble.get();
		SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bubble));
	}

	owner->AddComponent<ShootBubble>(m_bubbles);



	if (playerNumber == 1)
	{
		InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(owner, glm::vec3{ -1.f, 0.f, 0.f }, m_speed));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(owner, glm::vec3{ 1.f, 0.f, 0.f }, m_speed));
		InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<JumpCommand>(owner), KeyState::ButtonUp);
		InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<ShootCommand>(owner), KeyState::ButtonUp);

		InputManager::GetInstance().AddController();
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(owner, glm::vec3{ -1.f, 0.f, 0.f }, m_speed));
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(owner, glm::vec3{ 1.f, 0.f, 0.f }, m_speed));
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::A, std::make_unique<JumpCommand>(owner), KeyState::ButtonUp);
		InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::B, std::make_unique<ShootCommand>(owner), KeyState::ButtonUp);
	}
	if (playerNumber == 2)
	{
		InputManager::GetInstance().AddController();
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(owner, glm::vec3{ -1.f, 0.f, 0.f }, m_speed));
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(owner, glm::vec3{ 1.f, 0.f, 0.f }, m_speed));
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::A, std::make_unique<JumpCommand>(owner), KeyState::ButtonUp);
		InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::B, std::make_unique<ShootCommand>(owner), KeyState::ButtonUp);
	}







}

