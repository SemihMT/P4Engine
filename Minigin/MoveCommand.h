#pragma once
#include "GameObjectCommand.h"
#include "TimeManager.h"

namespace dae
{
	class MoveCommand final : public GameObjectCommand
	{
	public:
		 MoveCommand(GameObject* gameObject, const glm::vec3& normalizedDirection, float speed = 1.0f)
			: GameObjectCommand(gameObject),
			m_direction(normalizedDirection),
			m_speed(speed)
		{
		}

		void Execute() override
		{
			const auto t = GetGameObject()->GetTransform();
			t->Translate(m_direction * static_cast<float>(TimeManager::GetInstance().DeltaTime()) * m_speed);
			
		}
	private:
		glm::vec3 m_direction{};
		float m_speed{};
	};
}
