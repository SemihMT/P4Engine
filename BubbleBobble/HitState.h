#pragma once
#include <State.h>

#include "Subject.h"

namespace dae
{
	class HitState final : public State, public Subject
	{
	public:
		explicit HitState(GameObject* owner, int playerNumber);

		~HitState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		int m_playerNumber{};
		float m_timer{};
		float m_hitDuration{3.0f};
	};
}

