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
		const auto health = data.Get<int>("Score");
		scoreDisplay->SetText("Score: " + std::to_string(health));
	}
}
