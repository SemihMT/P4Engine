#include "BubbleMovementComponent.h"

#include "GameObject.h"

dae::BubbleMovementComponent::BubbleMovementComponent(GameObject* owner) :
	BaseComponent(owner),
	m_transform{GetOwner()->GetTransform()}
{
}

void dae::BubbleMovementComponent::Update()
{
	m_transform->Translate(m_direction * m_movementSpeed);
}

void dae::BubbleMovementComponent::SetMovementDirection(const glm::vec3& dir)
{
	m_direction = dir;
}
