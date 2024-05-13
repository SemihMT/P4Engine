#include "StateComponent.h"

dae::StateComponent::StateComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::StateComponent::SetState(std::unique_ptr<State> newState)
{
	m_currentState = std::move(newState);
}

void dae::StateComponent::Update()
{
	m_currentState->Update();
}
