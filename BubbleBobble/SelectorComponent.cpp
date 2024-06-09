#include "SelectorComponent.h"

#include "Components.h"
#include "GameObject.h"
#include "GameSettings.h"
#include "InputManager.h"

dae::SelectorComponent::SelectorComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::SelectorComponent::Update()
{
	if (InputManager::GetInstance().IsPressed(SDLK_DOWN))
	{
		Increment();
	}
	if (InputManager::GetInstance().IsPressed(SDLK_UP))
	{
		Decrement();
	}

	if(InputManager::GetInstance().IsPressed(SDLK_RETURN))
	{
		GameSettings::GetInstance().SetGameState(static_cast<GameSettings::GameState>(m_currentSelection),1);
	}
}

void dae::SelectorComponent::Increment()
{
	m_currentSelection += 1;
	m_currentSelection %= 3;

	GetOwner()->GetTransform()->SetLocalPosition(100.0f, static_cast<float>(m_currentSelection) * 100.0f + 150.0f, 0);
}

void dae::SelectorComponent::Decrement()
{
	m_currentSelection -= 1;
	m_currentSelection = (m_currentSelection + 3) % 3;

	GetOwner()->GetTransform()->SetLocalPosition(100.0f, static_cast<float>(m_currentSelection) * 100.0f + 150.0f, 0);
}
