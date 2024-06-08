#pragma once
#include <State.h>

#include "Subject.h"

namespace dae
{
	class ShootState final : public State, public Subject
	{
	public:
		explicit ShootState(GameObject* owner);

		~ShootState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		float m_timer{};
		float m_hitDuration{ 1.0f };
	};
}

