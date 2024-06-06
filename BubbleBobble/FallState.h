#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class FallState final : public State, public Subject
	{
	public:
		explicit FallState(GameObject* owner);

		~FallState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	};
}


