#pragma once
#include <State.h>
namespace dae
{
	class JumpState final : public State
	{
	public:
		explicit JumpState(GameObject* owner);

		~JumpState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	};
};


