#pragma once

#include "State.h"
#include "StateComponent.h"
#include "Subject.h"


namespace dae
{
	
	class IdleState final : public State, public Subject
	{
	public:
		explicit IdleState(GameObject* owner, int playerNumber);

		~IdleState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;

	private:
		int m_playerNumber{};
	};
}
