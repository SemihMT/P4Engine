#include "HitState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "PlayerComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "RigidBodyComponent.h"
#include "SpawnState.h"
#include "TimeManager.h"

dae::HitState::HitState(GameObject* owner, int playerNumber) : State(owner), m_playerNumber(playerNumber)
{
}

dae::HitState::~HitState()
{
}

void dae::HitState::OnEnter()
{
	if (std::is_base_of_v<Observer, PlayerEventHandlerComponent>)
		AddObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());


	GetOwner()->GetComponent<ColliderComponent>()->Disable();
	GetOwner()->GetComponent<RigidBodyComponent>()->Disable();
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Death");
	}
}

void dae::HitState::OnExit()
{
	RemoveObserver(GetOwner()->GetComponent<PlayerEventHandlerComponent>());
}

void dae::HitState::Update()
{
	m_timer += static_cast<float>(TimeManager::GetInstance().DeltaTime());
	if(m_timer >= m_hitDuration)
	{
		auto pos = GetOwner()->GetComponent<PlayerComponent>()->GetSpawnPosition();
		auto dir = GetOwner()->GetComponent<PlayerComponent>()->GetSpawnDirection();
		std::unique_ptr<State> spawnState = std::make_unique<SpawnState>(GetOwner(),pos,dir,m_playerNumber);
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(spawnState));
	}
}
