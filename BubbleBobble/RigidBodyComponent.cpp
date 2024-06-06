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
	const float dt{ static_cast<float>(TimeManager::GetInstance().DeltaTime()) };

	if (m_collider->IsCollidingBottom())
	{
		m_shouldFall = false;
		if (!m_isJumping)
		{
			m_verticalVelocity = 0.0f; // Reset vertical velocity when grounded
		}
	}
	else
	{
		m_shouldFall = true;

		// Apply gravity
		m_verticalVelocity += m_gravity * dt;

		// Apply additional force when moving left or right in the air
		if (InputManager::GetInstance().IsDown(SDLK_LEFT) || InputManager::GetInstance().IsDown(SDLK_RIGHT))
		{
			m_verticalVelocity += m_horizontalAirControlForce * dt;
		}
		else
		{
			// Apply a bigger force if there is no input while in the air
			m_verticalVelocity += m_idleAirForce * dt;
		}
	}

	// Apply vertical velocity to the transform
	m_transform->Translate(0.0f, m_verticalVelocity * dt, 0.0f);

	// Update jumping state based on vertical velocity
	if (m_collider->IsCollidingBottom() && m_verticalVelocity >= 0.0f)
	{
		m_isJumping = false;
	}
}

void RigidBodyComponent::Jump()
{
	if (m_collider->IsCollidingBottom())
	{
		m_verticalVelocity = m_jumpVelocity;
		m_isJumping = true;
	}
}
