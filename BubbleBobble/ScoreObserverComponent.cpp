#include "ScoreObserverComponent.h"

#include "GameObject.h"
#include "PlayerComponent.h"
#include "Text.h"

dae::ScoreObserverComponent::ScoreObserverComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::ScoreObserverComponent::OnNotify(Event event, const EventData& data)
{
	if (event == Event::Item_Collected)
	{
		const auto scoreDisplay = GetOwner()->GetComponent<Text>();
		const auto player = data.Get<GameObject*>("Player");
		if (player->GetComponent<PlayerComponent>()->GetPlayerNumber() == 1)
			m_player1Score = data.Get<int>("Score");
		else
			m_player2Score = data.Get<int>("Score");

		scoreDisplay->SetText("Score: " + std::to_string(m_player1Score) + "        Score: " + std::to_string(m_player2Score));
	}
}
