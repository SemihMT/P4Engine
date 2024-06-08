#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class ZenChanSpawnState final : public State, public Subject
	{
	public:
		explicit ZenChanSpawnState(GameObject* owner);

		~ZenChanSpawnState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
		
	};
}

