#include "ZenChanSpawnState.h"

#include "StateComponent.h"
#include "ZenChanCalmState.h"

dae::ZenChanSpawnState::ZenChanSpawnState(GameObject* owner) : State(owner)
{
}

dae::ZenChanSpawnState::~ZenChanSpawnState()
{
}

void dae::ZenChanSpawnState::OnEnter()
{
}

void dae::ZenChanSpawnState::OnExit()
{
}

void dae::ZenChanSpawnState::Update()
{
	
	GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<ZenChanCalmState>(GetOwner()));
}
