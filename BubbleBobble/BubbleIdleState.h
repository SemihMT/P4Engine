#pragma once
#include "BubbleComponent.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class BubbleIdleState final : public State, public Subject
	{
	public:
		explicit BubbleIdleState(GameObject* owner);

		~BubbleIdleState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		float m_popTimer{};
		float m_popTime{5.0f};

	};
}


