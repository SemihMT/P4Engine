#include "PhysicsComponent.h"

#include <algorithm>

#include "ColliderComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

using namespace dae;

PhysicsComponent::PhysicsComponent(GameObject* owner) : BaseComponent(owner), m_transform(owner->GetTransform()), m_collider{ owner->GetComponent<ColliderComponent>() }
{
}

void PhysicsComponent::Update()
{
	const auto result = m_collider->IsColliding();

	//If none of the collisions this frame are on the bottom (nothing under us)
	//shouldfall = true
	m_shouldFall = std::ranges::none_of(result,
		[](const auto& r) { return r.collisionSide == ColliderComponent::CollisionSide::Bottom; });


	if (m_shouldFall)
	{
		const float dt{ static_cast<float>(TimeManager::GetInstance().DeltaTime()) };
		m_currentFallSpeed += m_fallSpeed * dt;
		m_currentFallSpeed = std::clamp(m_currentFallSpeed, 0.0f, m_maxSpeed * dt);
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
