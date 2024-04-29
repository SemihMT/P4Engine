#include "BubbleMovementComponent.h"

#include "GameObject.h"

dae::BubbleMovementComponent::BubbleMovementComponent(GameObject* owner) : BaseComponent(owner), m_pTransform{ GetOwner()->GetTransform() }
{
}

void dae::BubbleMovementComponent::Update()
{
	m_pTransform->Translate(glm::vec3{ 1,0,0 } * m_movementSpeed);
}
