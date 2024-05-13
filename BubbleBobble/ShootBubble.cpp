#include "ShootBubble.h"

#include "BubbleMovementComponent.h"
#include "GameObject.h"

dae::ShootBubble::ShootBubble(GameObject* owner, GameObject* bubble) : BaseComponent(owner), m_pBubble{ bubble }
{
}

void dae::ShootBubble::Shoot() const
{
	const auto playerTransform = GetOwner()->GetTransform();
	const auto playerPos = playerTransform->GetWorldPosition();
	const auto playerDir = playerTransform->GetForwardDirection();
	const auto bubbleShootPos = playerPos + glm::vec3{ 10,0,0 } * playerDir;

	m_pBubble->GetTransform()->SetLocalPosition(bubbleShootPos);
	m_pBubble->GetComponent<BubbleMovementComponent>()->SetMovementDirection(playerDir);
	m_pBubble->Enable();
}
