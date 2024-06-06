#include "PlayerEventHandlerComponent.h"
#include <iostream>

dae::PlayerEventHandlerComponent::PlayerEventHandlerComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::PlayerEventHandlerComponent::OnNotify(Event event, const EventData& data)
{
	(void)data;
	//Events will come from states?
	switch (event)
	{
	case Event::Player_Spawn:
		std::cout << "Player notified from Spawn state;\n";
		//PlayerInit();
		break;
	case Event::Player_Idle:
		std::cout << "Player notified from the Idle state\n";
		break;
	case Event::Player_Death:
		/*if(m_health >= 0)
			PlayerRespawn();
		else*/

		break;
	case Event::Player_Respawn:
		break;
	case Event::Player_Damaged:
		//PlayerDamage();
		break;
	case Event::Player_ShootBubble:
		//SetState shoot
		break;
	case Event::Player_Jump:

		break;

	case Event::Bubble_HitEnemy:
		break;
	case Event::Bubble_PopEnemy:
		break;
	case Event::Bubble_PopNoEnemy:
		break;
	case Event::Item_Collected:
		break;
	}
}
