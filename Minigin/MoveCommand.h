﻿#pragma once
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
		MoveCommand(GameObject* gameObject,float speed = 1.0f)
			: GameObjectCommand(gameObject),
			m_direction(glm::vec3{}),
			m_speed(speed),
			m_useJoysticks(true)
		{
		}

		void Execute() override
		{
			const auto t = GetGameObject()->GetTransform();
			if (m_useJoysticks)
			{
				auto leftThumbStick = InputManager::GetInstance().GetLeftThumbDir(Controller::One);
				leftThumbStick.y *= -1;
				t->Translate(glm::vec3{ leftThumbStick,0 });
			}
			else
				t->Translate(m_direction * static_cast<float>(TimeManager::GetInstance().DeltaTime()) * m_speed);



		}
	private:
		glm::vec3 m_direction{};
		float m_speed{};
		bool m_useJoysticks{ false };
	};
}
