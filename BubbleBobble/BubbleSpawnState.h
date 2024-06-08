#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class BubbleSpawnState final : public State, public Subject
	{
	public:
		explicit BubbleSpawnState(GameObject* owner);

		~BubbleSpawnState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
		
	};
}


