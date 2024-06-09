#include "MaitaVersusHitState.h"

#include "AnimationComponent.h"
#include "MaitaVersusComponent.h"
#include "MaitaVersusFightState.h"
#include "RigidBodyComponent.h"
#include "SpawnState.h"
#include "TimeManager.h"

dae::MaitaVersusHitState::MaitaVersusHitState(GameObject* owner) : State(owner)
{
}

dae::MaitaVersusHitState::~MaitaVersusHitState()
{
}

void dae::MaitaVersusHitState::OnEnter()
{
	GetOwner()->GetComponent<ColliderComponent>()->Disable();
	GetOwner()->GetComponent<RigidBodyComponent>()->Disable();
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Death");
	}
}

void dae::MaitaVersusHitState::OnExit()
{
}

void dae::MaitaVersusHitState::Update()
{
	m_timer += static_cast<float>(TimeManager::GetInstance().DeltaTime());
	if(m_timer >= m_hitDuration)
	{
		auto pos = GetOwner()->GetComponent<MaitaVersusComponent>()->GetSpawnPos();
		auto dir = GetOwner()->GetComponent<MaitaVersusComponent>()->GetSpawnDir();
		std::unique_ptr<State> fightState = std::make_unique<MaitaVersusFightState>(GetOwner(), pos, dir);
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(fightState));
	}
}
