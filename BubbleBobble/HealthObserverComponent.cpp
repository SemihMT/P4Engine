#include "HealthObserverComponent.h"

#include "GameObject.h"
#include "GameSettings.h"
#include "PlayerComponent.h"
#include "Text.h"

dae::HealthObserverComponent::HealthObserverComponent(GameObject* owner) : BaseComponent(owner)
{
	const auto lifeDisplay = GetOwner()->GetComponent<Text>();
	lifeDisplay->SetText("     " + std::to_string(m_player1Health) + "                                          " + std::to_string(m_player2Health));
}

void dae::HealthObserverComponent::OnNotify(Event event, const EventData& data)
{
	if (event == Event::Player_Damaged)
	{
		const auto lifeDisplay = GetOwner()->GetComponent<Text>();

		const auto player = data.Get<GameObject*>("Player");
		if (player->GetComponent<PlayerComponent>()->GetPlayerNumber() == 1)
			m_player1Health = data.Get<int>("Health");
		else
			m_player2Health = data.Get<int>("Health");

		lifeDisplay->SetText("     " + std::to_string(m_player1Health) + "                                          " + std::to_string(m_player2Health));
	}

	if(event == Event::Player_Death)
	{
		GameSettings::GetInstance().SetGameState(GameSettings::GameState::Gameover,-1);
	}
}

void dae::HealthObserverComponent::Init(int player1Health,int player2Health)
{
	m_player1Health = player1Health;
	m_player2Health = player2Health;
	const auto lifeDisplay = GetOwner()->GetComponent<Text>();
	lifeDisplay->SetText("     " + std::to_string(m_player1Health) + "                                          " + std::to_string(m_player2Health));
}
