#include "IdentifierComponent.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "GameObject.h"
#include "GameSettings.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Text.h"

dae::IdentifierComponent::IdentifierComponent(GameObject* owner) : BaseComponent(owner)
{
	if (auto* textComponent = GetOwner()->GetComponent<Text>())
	{
		textComponent->SetText(m_identifier + "  -  " + std::to_string(GameSettings::GetInstance().GetScore()));
	}
}

void dae::IdentifierComponent::Update()
{
	if (InputManager::GetInstance().IsDown(Controller::One, XInputController::Button::DPAD_RIGHT) ||
		InputManager::GetInstance().IsDown(SDLK_RIGHT))
	{
		m_index += 1;
		m_index = std::clamp(m_index, 0, 2);
	}
	if (InputManager::GetInstance().IsDown(Controller::One, XInputController::Button::DPAD_LEFT) ||
		InputManager::GetInstance().IsDown(SDLK_LEFT))
	{
		m_index -= 1;
		m_index = std::clamp(m_index, 0, 2);
	}

	if (InputManager::GetInstance().IsDown(Controller::One, XInputController::Button::DPAD_UP) ||
		InputManager::GetInstance().IsDown(SDLK_UP))
	{
		if (m_identifier[m_index] == 'Z')
		{
			m_identifier[m_index] = 'A';
		}
		else
		{
			m_identifier[m_index] += 1;
		}
		if (auto* textComponent = GetOwner()->GetComponent<Text>())
		{
			textComponent->SetText(m_identifier + "  -  " + std::to_string(GameSettings::GetInstance().GetScore()));
		}
	}
	if (InputManager::GetInstance().IsDown(Controller::One, XInputController::Button::DPAD_DOWN) ||
		InputManager::GetInstance().IsDown(SDLK_DOWN))
	{
		if (m_identifier[m_index] == 'A')
		{
			m_identifier[m_index] = 'Z';
		}
		else
		{
			m_identifier[m_index] -= 1;
		}
		if (auto* textComponent = GetOwner()->GetComponent<Text>())
		{
			textComponent->SetText(m_identifier + "  -  " + std::to_string(GameSettings::GetInstance().GetScore()));
		}
	}

	if (InputManager::GetInstance().IsDown(Controller::One, XInputController::Button::A) ||
		InputManager::GetInstance().IsDown(SDLK_RETURN))
	{
		WriteHighscore();
	}
}

void dae::IdentifierComponent::WriteHighscore()
{
	std::ofstream file(ResourceManager::GetInstance().GetDataPath() + "Highscores.txt");
	if (!file)
	{
		return;
	}

	file << m_identifier << "  -  " << std::to_string(GameSettings::GetInstance().GetScore()) << "\n";

	if (auto* textComponent = GetOwner()->GetComponent<Text>())
	{
		textComponent->SetText("Highscore written!");
	}

}
