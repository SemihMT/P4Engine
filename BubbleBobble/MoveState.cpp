#include "MoveState.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "FallState.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpState.h"
#include "PlayerComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "TimeManager.h"

dae::MoveState::MoveState(GameObject* owner, int playerNumber) :
	State{ owner },
	m_playerNumber(playerNumber),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>()),
	m_rb(GetOwner()->GetComponent<RigidBodyComponent>())
{
}

dae::MoveState::~MoveState()
{
}

void dae::MoveState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());

	m_animationComponent->SetCurrentAnimation("Walk");
	EventData d{};
	d.data["Player"] = GetOwner();
	Notify(Event::Player_Move, d);

}

void dae::MoveState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::MoveState::Update()
{

	auto& inputManager = InputManager::GetInstance();

	if (m_playerNumber == 1)
	{
		bool playerIsMoving =
			inputManager.IsDown(SDLK_LEFT) ||
			inputManager.IsDown(SDLK_RIGHT) ||
			inputManager.IsPressed(Controller::One, XInputController::Button::DPAD_LEFT) ||
			inputManager.IsPressed(Controller::One, XInputController::Button::DPAD_RIGHT);
		if (!playerIsMoving)
		{
			std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner(),m_playerNumber);
			GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
			return;
		}
	}
	if (m_playerNumber == 2)
	{
		bool playerIsMoving =
			inputManager.IsPressed(Controller::Two, XInputController::Button::DPAD_LEFT) ||
			inputManager.IsPressed(Controller::Two, XInputController::Button::DPAD_RIGHT);
		if (!playerIsMoving)
		{
			std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner(),m_playerNumber);
			GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
			std::cout << "Switching to IdleState\n";
			return;
		}
	}
	if (m_rb->GetVerticalVelocity() > 0)
	{
		std::unique_ptr<State> fallState = std::make_unique<FallState>(GetOwner(),m_playerNumber);
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(fallState));
	}
}
