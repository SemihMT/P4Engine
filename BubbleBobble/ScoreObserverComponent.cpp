#include "ScoreObserverComponent.h"

#include "GameObject.h"
#include "PlayerComponent.h"
#include "Text.h"

dae::ScoreObserverComponent::ScoreObserverComponent(GameObject* owner) : BaseComponent(owner)
{
	const auto scoreDisplay = GetOwner()->GetComponent<Text>();
	scoreDisplay->SetText("" + std::to_string(m_player1Score) + "                                               " + std::to_string(m_player2Score));

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

		scoreDisplay->SetText("" + std::to_string(m_player1Score) + "                                               " + std::to_string(m_player2Score));
	}
}

void dae::ScoreObserverComponent::Init(int player1Score, int player2Score)
{
	m_player1Score = player1Score;
	m_player2Score = player2Score;
	const auto scoreDisplay = GetOwner()->GetComponent<Text>();
	scoreDisplay->SetText("" + std::to_string(m_player1Score) + "                                               " + std::to_string(m_player2Score));
}
