#pragma once
#include <State.h>

#include "Subject.h"

namespace dae
{
	class ShootState final : public State, public Subject
	{
	public:
		explicit ShootState(GameObject* owner, int playerNumber);

		~ShootState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		int m_playerNumber{};
		float m_timer{};
		float m_hitDuration{ 1.0f };
	};
}

