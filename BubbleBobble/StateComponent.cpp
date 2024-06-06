#include "StateComponent.h"

dae::StateComponent::StateComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::StateComponent::SetState(std::unique_ptr<State> newState)
{
	if(m_currentState)
		m_currentState->OnExit();
	m_currentState = std::move(newState);
	m_currentState->OnEnter();
}

void dae::StateComponent::Update()
{
	if (m_currentState)
		m_currentState->Update();
}
