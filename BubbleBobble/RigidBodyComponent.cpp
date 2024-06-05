#include "RigidBodyComponent.h"

#include <algorithm>
#include <SDL_keycode.h>

#include "ColliderComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TimeManager.h"

using namespace dae;

RigidBodyComponent::RigidBodyComponent(GameObject* owner) : BaseComponent(owner), m_transform(owner->GetTransform()), m_collider{ owner->GetComponent<ColliderComponent>() }
{
}

void RigidBodyComponent::Update()
{
	m_shouldFall = !m_collider->IsCollidingBottom();

	const float dt{ static_cast<float>(TimeManager::GetInstance().DeltaTime()) };

	if (m_shouldFall)
	{
		// Apply gravity
		m_verticalVelocity += 98.1f * dt; // Gravity pulling downwards
	}
	else
	{
		if (!m_isJumping)
			m_verticalVelocity = 0.0f; // Reset vertical velocity when grounded
	}

	// Apply vertical velocity
	m_transform->Translate(0, m_verticalVelocity * dt, 0);
}

void RigidBodyComponent::ToggleGravity()
{
	m_shouldFall = !m_shouldFall;
}

bool RigidBodyComponent::IsGravityEnabled() const
{
	return m_shouldFall;
}

void RigidBodyComponent::SetVerticalVelocity(float verticalVelocity)
{
	m_verticalVelocity = verticalVelocity;
}

void RigidBodyComponent::SetIsJumping(bool jump)
{
	m_isJumping = jump;
}
