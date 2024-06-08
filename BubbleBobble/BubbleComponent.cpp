#include "BubbleComponent.h"

#include "AnimationComponent.h"
#include "BubbleEventHandlerComponent.h"
#include "BubbleMovementComponent.h"
#include "BubbleSpawnState.h"
#include "ColliderComponent.h"
#include "StateComponent.h"

dae::BubbleComponent::BubbleComponent(GameObject* owner, const std::string& spriteSheet) : BaseComponent(owner),
                                                                                           m_spriteSheet{spriteSheet}
{
	owner->SetName("Bubble");
	owner->GetTransform()->SetLocalPosition(-100.0f,-100.f,0);

	
	owner->AddComponent<AnimationComponent>(m_spriteSheet);
	owner->GetComponent<AnimationComponent>()->SetDestinationSize(glm::vec2{ static_cast<float>(m_dstSize) });
	//owner->AddComponent<BubbleMovementComponent>();

	int row{ 4 };
	int numFrames{ 3 };
	AnimationData spawnBubbleAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("BubbleSpawn", spawnBubbleAnimation);

	row = 5;
	numFrames = 1;
	AnimationData idleBubbleAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("BubbleIdle", idleBubbleAnimation);

	row = 6;
	numFrames = 2;
	AnimationData popBubbleAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("BubblePop", popBubbleAnimation);

	const auto observer = GetOwner()->AddComponent<BubbleEventHandlerComponent>();
	owner->AddComponent<StateComponent>();
	owner->GetComponent<StateComponent>()->SetState(std::make_unique<BubbleSpawnState>(owner));
	owner->AddComponent<ColliderComponent>(m_dstSize, ColliderType::Trigger)->AddObserver(observer);
}
