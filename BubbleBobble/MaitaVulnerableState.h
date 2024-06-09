﻿#pragma once
#include "AnimationComponent.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class MaitaVulnerableState final : public State, public Subject
	{
	public:
		explicit MaitaVulnerableState(GameObject* owner);

		~MaitaVulnerableState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		AnimationComponent* m_animationComponent{};
		float m_maxVulnerableTime{ 15.0f };
		float m_angryTime{ 10.0f };
		float m_respawnTimer{ 0.0f };

	};
}
