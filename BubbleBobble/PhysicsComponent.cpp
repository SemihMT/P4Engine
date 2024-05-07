#include "PhysicsComponent.h"

#include "GameObject.h"
#include "TimeManager.h"

using namespace dae;

PhysicsComponent::PhysicsComponent(GameObject* owner) : BaseComponent(owner), m_transform(owner->GetTransform())
{
}

void PhysicsComponent::Update()
{
	if(m_shouldFall)
	{
		const float dt{ static_cast<float>(TimeManager::GetInstance().DeltaTime()) };
		m_currentFallSpeed += m_fallSpeed * dt;
		m_transform->Translate(0, m_currentFallSpeed, 0);
	}
}

void PhysicsComponent::ToggleGravity()
{
	m_shouldFall = !m_shouldFall;
}

bool PhysicsComponent::IsGravityEnabled() const
{
	return m_shouldFall;
}
