#include "HealthObserverComponent.h"

#include "GameObject.h"
#include "PlayerComponent.h"
#include "Text.h"

dae::HealthObserverComponent::HealthObserverComponent(GameObject* owner): BaseComponent(owner)
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
}
