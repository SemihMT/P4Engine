#include "BubbleEventHandlerComponent.h"

#include <iostream>

#include "BubblePopState.h"
#include "BubbleSpawnState.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "ZenChanCalmState.h"
#include "ZenChanVulnerableState.h"

dae::BubbleEventHandlerComponent::BubbleEventHandlerComponent(GameObject* owner) : BaseComponent(owner)
{
}

void dae::BubbleEventHandlerComponent::OnNotify(Event event, const EventData& data)
{

	switch (event)
	{
	case Event::Bubble_HitEnemy:
	{
		std::cout << "Bubble hit enemy!\n";

		//Set self state to pop/spawn
		auto bubbleThatHit = data.Get<GameObject*>("Bubble");
		auto stateComp = bubbleThatHit->GetComponent<StateComponent>();
		stateComp->SetState(std::make_unique<BubbleSpawnState>(bubbleThatHit));
		//Set enemy state to hit
		auto enemyThatGotHit = data.Get<GameObject*>("HitEnemy");
		stateComp = enemyThatGotHit->GetComponent<StateComponent>();
		auto state = enemyThatGotHit->GetName() == "ZenChan" ? std::make_unique<ZenChanVulnerableState>(enemyThatGotHit) : nullptr;/*std::make_unique<MaitaVulnerableState>(enemyThatGotHit);*/
		stateComp->SetState(std::move(state));
	}
	break;
	
	case Event::Bubble_PopNoEnemy:
		{
			std::cout << "Bubble should pop!\n";
			//Set self state to pop/spawn
			auto bubbleThatHit = data.Get<GameObject*>("Bubble");
			auto stateComp = bubbleThatHit->GetComponent<StateComponent>();
			stateComp->SetState(std::make_unique<BubblePopState>(bubbleThatHit));
		}
		break;
	case Event::Bubble_Spawn:
		std::cout << "Bubble Spawned!\n";
		break;
	case Event::Bubble_Shot:
		break;
	case Event::Bubble_PlayerJump:
		{
			std::cout << "Player jumped on bubble!\n";
			auto player = data.Get<GameObject*>("Player");
			auto bubble = data.Get<GameObject*>("Bubble");
			auto rb = player->GetComponent<RigidBodyComponent>();
			auto collider = player->GetComponent<ColliderComponent>();
			rb->JumpNoCollisionCheck();
			collider->StartJumping();
			bubble->GetComponent<StateComponent>()->SetState(std::make_unique<BubbleSpawnState>(bubble));
		}
		break;
	case Event::Item_Collected:
		break;
	}
}

void dae::BubbleEventHandlerComponent::Update()
{
}
