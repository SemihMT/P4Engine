#include "ShootBubble.h"

#include "BubbleMovementComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "StateComponent.h"

dae::ShootBubble::ShootBubble(GameObject* owner) : BaseComponent(owner),
                                                   m_bubble{std::make_unique<GameObject>(-100,-100,0)}
{
	m_bubble->AddComponent<StateComponent>()->SetState();
}

void dae::ShootBubble::Shoot() const
{
	const auto playerTransform = GetOwner()->GetTransform();
	const auto playerPos = playerTransform->GetWorldPosition();
	const auto playerDir = playerTransform->GetForwardDirection();
	const auto bubbleShootPos = playerPos + glm::vec3{ 10,0,0 } * playerDir;

	/*m_pBubble->GetTransform()->SetLocalPosition(bubbleShootPos);
	m_pBubble->GetComponent<BubbleMovementComponent>()->SetMovementDirection(playerDir);
	m_pBubble->Enable();*/
}
