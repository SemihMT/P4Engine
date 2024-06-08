#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class BubblePopState final : public State, public Subject
	{
	public:
		explicit BubblePopState(GameObject* owner);

		~BubblePopState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		float m_popTimer{};
		float m_popTime{2.0f};

	};
}


