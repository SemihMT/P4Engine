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
		const auto health = data.Get<int>("Health");
		lifeDisplay->SetText("# Lives: " + std::to_string(health));
	}
}
