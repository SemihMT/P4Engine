#include "ScoreObserverComponent.h"

#include "GameObject.h"
#include "Text.h"

dae::ScoreObserverComponent::ScoreObserverComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::ScoreObserverComponent::OnNotify(Event event, const EventData& data)
{
	if (event == Event::Score_Add)
	{
		const auto scoreDisplay = GetOwner()->GetComponent<Text>();
		const auto player = data.Get<GameObject*>("Player");
		if (player->GetName().find('1') != std::string::npos)
			m_player1Score = data.Get<int>("Score");
		else
			m_player2Score = data.Get<int>("Score");

		scoreDisplay->SetText("Score: " + std::to_string(m_player1Score) + "\n\nScore: " + std::to_string(m_player2Score));
	}
}
