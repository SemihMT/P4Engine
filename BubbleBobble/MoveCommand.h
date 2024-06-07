#pragma once
#include "GameObjectCommand.h"
#include "MoveState.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

namespace dae
{
	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* gameObject, const glm::vec3& normalizedDirection, float speed = 1.0f)
			: GameObjectCommand(gameObject),
			m_transform(gameObject->GetTransform()),
			m_collider(gameObject->GetComponent<ColliderComponent>()),
			m_direction(normalizedDirection),
			m_speed(speed)
		{
		}
		void Execute() override
		{
			m_transform->SetForwardDirection(m_direction);
			bool goingLeftWhileTouchingLeft = m_collider->IsCollidingLeft() && m_direction == glm::vec3{ -1,0,0 };
			bool goingRightWhileTouchingRight = m_collider->IsCollidingRight() && m_direction == glm::vec3{ 1,0,0 };

			if (!(goingLeftWhileTouchingLeft && goingRightWhileTouchingRight))
			{
				m_transform->Translate(m_direction * static_cast<float>(TimeManager::GetInstance().DeltaTime()) * m_speed);
			}
		}
	private:
		Transform* m_transform{};
		ColliderComponent* m_collider{};
		glm::vec3 m_direction{};
		float m_speed{};
	};
}
