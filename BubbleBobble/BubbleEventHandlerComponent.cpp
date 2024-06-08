#include "BubbleEventHandlerComponent.h"

#include <iostream>

dae::BubbleEventHandlerComponent::BubbleEventHandlerComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::BubbleEventHandlerComponent::OnNotify(Event event, const EventData& data)
{
	(void)data;
	switch (event)
	{
	case Event::Bubble_HitEnemy:
		std::cout << "Bubble hit enemy!\n";
		//Set self state to pop/spawn
		//Set enemy state to hit
		break;
	case Event::Bubble_PopEnemy:
		break;
	case Event::Bubble_PopNoEnemy:
		std::cout << "Bubble should pop!\n";
		break;
	case Event::Bubble_Spawn:
		std::cout << "Bubble Spawned!\n";
		break;
	case Event::Bubble_Shot:
		break;
	case Event::Bubble_PlayerJump:
		std::cout << "Player jumped on bubble!\n";
		break;
	case Event::Item_Collected:
		break;
	}
}

void dae::BubbleEventHandlerComponent::Update()
{
}
