#include "ShootBubble.h"

#include "GameObject.h"

dae::ShootBubble::ShootBubble(GameObject* owner, GameObject* bubble) : BaseComponent(owner), m_pBubble{ bubble }
{
}

void dae::ShootBubble::Shoot() const
{
	m_pBubble->GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetWorldPosition() + glm::vec3{10,0,0});
	m_pBubble->Enable();
}
