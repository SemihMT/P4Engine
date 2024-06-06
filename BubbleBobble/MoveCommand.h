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
			m_direction(normalizedDirection),
			m_speed(speed)
		{
		}
		void Execute() override
		{
			auto stateComp = GetGameObject()->GetComponent<StateComponent>();
			State* currentState = stateComp->GetCurrentState();

			// Check if the current state is not a MoveState or if the direction needs to be updated
			MoveState* currentMoveState = dynamic_cast<MoveState*>(currentState);
			if (currentMoveState == nullptr || currentMoveState->GetDirection() != m_direction || currentMoveState->GetSpeed() != m_speed)
			{
				// Create a new MoveState and set it as the current state
				auto moveState = std::make_unique<MoveState>(GetGameObject(), m_direction, m_speed);
				stateComp->SetState(std::move(moveState));
			}
		}
	private:
		glm::vec3 m_direction{};
		float m_speed{};
	};
}
