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
		explicit MoveState(GameObject* owner, int playerNumber);

		~MoveState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		int m_playerNumber{};
		Transform* m_transform{};
		AnimationComponent* m_animationComponent{};
		RigidBodyComponent* m_rb{};
		ColliderComponent* m_collider{};
	};
}
