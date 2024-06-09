#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class MaitaSpawnState final : public State, public Subject
	{
	public:
		explicit MaitaSpawnState(GameObject* owner);

		~MaitaSpawnState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
		
	};
}

