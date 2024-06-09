#include "MaitaSpawnState.h"

#include "MaitaChaseState.h"
#include "StateComponent.h"

dae::MaitaSpawnState::MaitaSpawnState(GameObject* owner) : State(owner)
{
}

dae::MaitaSpawnState::~MaitaSpawnState()
{
}

void dae::MaitaSpawnState::OnEnter()
{
}

void dae::MaitaSpawnState::OnExit()
{
}

void dae::MaitaSpawnState::Update()
{
	GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<MaitaChaseState>(GetOwner()));
}
