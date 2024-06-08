#include "FallState.h"

#include "AnimationComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "ColliderComponent.h"
#include "IdleState.h"


dae::FallState::FallState(GameObject* owner, int playerNumber) : State(owner), m_playerNumber(playerNumber)
{
}

dae::FallState::~FallState()
{
}

void dae::FallState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());

	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("FallDown");
	}

	EventData d{};
	d.data["Player"] = GetOwner();
	Notify(Event::Player_Fall, d);


	GetOwner()->GetComponent<ColliderComponent>()->Land();

}

void dae::FallState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::FallState::Update()
{
	if (GetOwner()->GetComponent<ColliderComponent>()->IsCollidingBottom())
	{
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner(), m_playerNumber);
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
		return;
	}

	if (GetOwner()->GetTransform()->GetLocalPosition().y > Renderer::GetInstance().GetWindowSize().y)
	{
		auto pos = GetOwner()->GetTransform()->GetLocalPosition();
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, 0, pos.z);
	}
}
