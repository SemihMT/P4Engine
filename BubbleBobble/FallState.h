#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class FallState final : public State, public Subject
	{
	public:
		explicit FallState(GameObject* owner, int playerNumber);

		~FallState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		int m_playerNumber{};
	};
}


