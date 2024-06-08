#pragma once
#include "State.h"
#include "StateComponent.h"
#include "Subject.h"

namespace dae
{
	class SpawnState final : public State, public Subject
	{
	public:
		explicit SpawnState(GameObject* owner, const glm::vec3& spawnPos, const glm::vec3& spawnDirection, int playerNumber);

		~SpawnState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		glm::vec3 m_spawnPos{};
		glm::vec3 m_spawnDir{};
		int m_playerNumber;
	};
}