#include "ZenChanComponent.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "ZenChanCalmState.h"
#include "ZenChanSpawnState.h"

dae::ZenChanComponent::ZenChanComponent(GameObject* owner, const glm::vec3& direction, ColliderType type) : BaseComponent(owner),
                                                                                                            m_transform(owner->GetTransform())
{
	owner->SetName("ZenChan");
	
	owner->AddComponent<AnimationComponent>(m_spriteSheetPath);
	owner->GetComponent<AnimationComponent>()->SetDestinationSize(glm::vec2{static_cast<float>(m_dstSize)});

	int row = 0;
	int numFrames = 2;
	const AnimationData walkAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Walk", walkAnimation);

	row = 1;
	numFrames = 2;
	const AnimationData angryWalkAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("AngryWalk", angryWalkAnimation);

	row = 3;
	numFrames = 2;
	const AnimationData bubbleAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Bubble", bubbleAnimation);

	row = 5;
	numFrames = 2;
	const AnimationData angryBubbleAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("AngryBubble", angryBubbleAnimation);

	owner->AddComponent<ColliderComponent>(m_dstSize,type );
	owner->AddComponent<RigidBodyComponent>();
	owner->AddComponent<StateComponent>()->SetState(std::make_unique<ZenChanSpawnState>(owner));

	auto pos = m_transform->GetLocalPosition();
	m_transform->SetLocalPosition(pos.x * static_cast<float>(m_srcSize), pos.y * static_cast<float>(m_srcSize), pos.z);
	m_transform->SetForwardDirection(direction);
}

