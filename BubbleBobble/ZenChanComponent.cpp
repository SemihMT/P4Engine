#include "ZenChanComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "SpriteComponent.h"
#include "StateComponent.h"

dae::ZenChanComponent::ZenChanComponent(GameObject* owner, const glm::vec3& direction) : BaseComponent(owner),
                                                                                         m_transform(owner->GetTransform())
{
	owner->SetName("ZenChan");
	auto pos = m_transform->GetLocalPosition();
	m_transform->SetLocalPosition(pos.x * static_cast<float>(m_dstSize), pos.y * static_cast<float>(m_dstSize), pos.z);
	m_transform->SetForwardDirection(direction);
	owner->AddComponent<SpriteComponent>(m_spriteSheetPath, glm::ivec2{ m_srcSize }, m_tileRow, m_tileCol, glm::ivec2{m_dstSize});
	owner->AddComponent<ColliderComponent>(m_dstSize, false);
	owner->AddComponent<RigidBodyComponent>();
	owner->AddComponent<StateComponent>();
}
