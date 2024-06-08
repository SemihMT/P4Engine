#include "IdleState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "JumpState.h"
#include "MoveState.h"
#include "PlayerComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"

dae::IdleState::IdleState(GameObject* owner, int playerNumber) :State{ owner }, m_playerNumber(playerNumber)
{

}

dae::IdleState::~IdleState()
{
}

void dae::IdleState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());

	Notify(Event::Player_Idle, {});

	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Idle");
	}

}

void dae::IdleState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::IdleState::Update()
{

	auto& inputManager = InputManager::GetInstance();

	if (m_playerNumber == 1)
	{
		bool playerIsMoving =
			inputManager.IsDown(SDLK_LEFT) ||
			inputManager.IsDown(SDLK_RIGHT) ||
			inputManager.IsPressed(Controller::One, XInputController::Button::DPAD_LEFT) ||
			inputManager.IsPressed(Controller::One, XInputController::Button::DPAD_RIGHT);
		if (playerIsMoving)
		{
			std::unique_ptr<State> moveState = std::make_unique<MoveState>(GetOwner(), m_playerNumber);
			GetOwner()->GetComponent<StateComponent>()->SetState(std::move(moveState));
			return;
		}
	}
	if (m_playerNumber == 2)
	{
		bool playerIsMoving =
			inputManager.IsPressed(Controller::Two, XInputController::Button::DPAD_LEFT) ||
			inputManager.IsPressed(Controller::Two, XInputController::Button::DPAD_RIGHT);
		if (playerIsMoving)
		{
			std::unique_ptr<State> moveState = std::make_unique<MoveState>(GetOwner(), m_playerNumber);
			GetOwner()->GetComponent<StateComponent>()->SetState(std::move(moveState));
			return;
		}
	}


}
