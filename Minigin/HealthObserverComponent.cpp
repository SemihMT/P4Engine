#include "HealthObserverComponent.h"

#include "GameObject.h"
#include "Text.h"

dae::HealthObserverComponent::HealthObserverComponent(GameObject* owner): BaseComponent(owner)
{
}

void dae::HealthObserverComponent::OnNotify(Event event, const EventData& data)
{
	if(event == Event::Player_Damaged)
	{
		const auto lifeDisplay = GetOwner()->GetComponent<Text>();

		const auto player = data.Get<GameObject*>("Player");
		if (player->GetName().find('1') != std::string::npos)
			m_player1Health = data.Get<int>("Health");
		else
			m_player2Health = data.Get<int>("Health");
		
		lifeDisplay->SetText("# Lives: " + std::to_string(m_player1Health) + "\n\n# Lives: " + std::to_string(m_player2Health));
	}
}
