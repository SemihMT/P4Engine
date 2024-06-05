#pragma once
#include "GameObject.h"
#include "GameObjectCommand.h"
#include "TimeManager.h"
#include "RigidBodyComponent.h"
namespace dae
{
	class JumpCommand final : public GameObjectCommand
	{
	public:
		JumpCommand(GameObject* gameObject, float jumpForce = 10.0f)
			: GameObjectCommand(gameObject),
			m_jumpForce(jumpForce),
			m_transform(GetGameObject()->GetTransform()),
			m_rb(GetGameObject()->GetComponent<RigidBodyComponent>()),
			m_collider(GetGameObject()->GetComponent<ColliderComponent>())
		{
		}

		void Execute() override
		{
			if (m_rb && m_collider->IsCollidingBottom())
			{
				m_rb->SetVerticalVelocity(-m_jumpForce);
				m_rb->SetIsJumping(true);
			}
		}

	private:
		void ApplyJumpForce() const
		{
			// Apply the jump force
			float dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
			glm::vec3 jumpVelocity = glm::vec3(0, -m_jumpForce * dt, 0);
			m_transform->Translate(jumpVelocity);
		}

		float m_jumpForce;
		Transform* m_transform;
		RigidBodyComponent* m_rb;
		ColliderComponent* m_collider;
	};
}
