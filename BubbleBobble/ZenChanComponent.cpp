#include "ZenChanComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "SpriteComponent.h"
#include "StateComponent.h"

dae::ZenChanComponent::ZenChanComponent(GameObject* owner, const glm::vec3& direction, ColliderType type) : BaseComponent(owner),
                                                                                         m_transform(owner->GetTransform())
{
	owner->SetName("ZenChan");
	
	owner->AddComponent<SpriteComponent>(m_spriteSheetPath, glm::ivec2{ m_srcSize }, m_tileRow, m_tileCol, glm::ivec2{m_dstSize});
	owner->AddComponent<ColliderComponent>(m_dstSize,type );
	owner->AddComponent<RigidBodyComponent>();
	//owner->AddComponent<StateComponent>();

	auto pos = m_transform->GetLocalPosition();
	m_transform->SetLocalPosition(pos.x * static_cast<float>(m_srcSize), pos.y * static_cast<float>(m_srcSize), pos.z);
	m_transform->SetForwardDirection(direction);
}

