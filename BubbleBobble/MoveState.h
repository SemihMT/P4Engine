#pragma once
#include "AnimationComponent.h"
#include "RigidBodyComponent.h"
#include "State.h"
#include "Subject.h"

namespace dae
{

	class MoveState final : public State, public Subject
	{
	public:
		explicit MoveState(GameObject* owner, const glm::vec3& direction, float speed);

		~MoveState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;

		const glm::vec3& GetDirection() const { return m_direction; }
		float GetSpeed() const { return m_speed; }
	private:
		Transform* m_transform{};
		AnimationComponent* m_animationComponent{};
		RigidBodyComponent* m_rb{};
		ColliderComponent* m_collider{};
		glm::vec3 m_direction{};
		float m_speed{};
	};
}
