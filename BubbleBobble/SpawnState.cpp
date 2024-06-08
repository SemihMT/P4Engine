#include "SpawnState.h"

#include "ColliderComponent.h"
#include "IdleState.h"
#include "PlayerComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"

dae::SpawnState::SpawnState(GameObject* owner, const glm::vec3& spawnPos, const glm::vec3& spawnDirection, int playerNumber) :
	State(owner),
	m_spawnPos{ spawnPos },
	m_spawnDir{ spawnDirection },
	m_playerNumber{playerNumber}
{
}

dae::SpawnState::~SpawnState()
{
}

void dae::SpawnState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());

	EventData d{};
	d.data["PlayerNumber"] = m_playerNumber;
	Notify(Event::Player_Spawn, d);

	GetOwner()->GetTransform()->SetLocalPosition(m_spawnPos);
	GetOwner()->GetTransform()->SetForwardDirection(m_spawnDir);

	if(const auto collider = GetOwner()->GetComponent<ColliderComponent>())
		collider->Enable();
	if(const auto rigidBody = GetOwner()->GetComponent<RigidBodyComponent>())
		rigidBody->Enable();

	std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner(), m_playerNumber);
	GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
}

void dae::SpawnState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::SpawnState::Update()
{
}
