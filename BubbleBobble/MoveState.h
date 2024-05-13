#pragma once
#include "State.h"
#include "StateComponent.h"

namespace dae
{
	
	class MoveState final : public State
	{
	public:
		explicit MoveState(GameObject* owner);

		~MoveState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	};
}
