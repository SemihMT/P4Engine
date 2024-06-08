#pragma once
#include "AnimationComponent.h"
#include "RigidBodyComponent.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class ZenChanCalmState final : public State, public Subject
	{
	public:
		explicit ZenChanCalmState(GameObject* owner);

		~ZenChanCalmState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		void DecideNextAction();
		void MoveRight(float dt);
		void MoveLeft(float dt);
		void Jump();

		glm::vec2 m_directionToPlayer{};
		Transform* m_ownerTransform;
		RigidBodyComponent* m_ownerRb{};
		ColliderComponent* m_ownerCollider{};
		GameObject* m_chosenPlayer{};
		AnimationComponent* m_animationComponent{};

		float m_speed{ 75.0f };
		float m_timeSinceLastDecision{ 3.0f };
		float m_decisionInterval{ 3.0f }; // Time between decisions in seconds
		float m_angryTimer{0.0f};
		float m_timeUntilAngry{15.0f};
		bool m_shouldJump{ false };
		glm::vec2 m_horizontalDirection{ 0,0 };

	};
}

