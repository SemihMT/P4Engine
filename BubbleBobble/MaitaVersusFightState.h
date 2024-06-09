#pragma once
#include "State.h"
#include "Subject.h"

namespace dae
{
	class MaitaVersusFightState final : public State, public Subject
	{
	public:
		explicit MaitaVersusFightState(GameObject* owner, const glm::vec3& pos, const glm::vec3& dir );

		~MaitaVersusFightState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:

		glm::vec3 m_spawnPos{};
		glm::vec3 m_spawnDir{};
	};
}

