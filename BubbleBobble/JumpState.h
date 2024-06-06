#pragma once
#include <State.h>

#include "AnimationComponent.h"
#include "RigidBodyComponent.h"
#include "Subject.h"

namespace dae
{
	class JumpState final : public State, public Subject
	{
	public:
		explicit JumpState(GameObject* owner);

		~JumpState() override;
		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		AnimationComponent* m_animationComponent{};
		RigidBodyComponent* m_rb{};
	};
};


