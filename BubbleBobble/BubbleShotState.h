#pragma once
#include "BubbleComponent.h"
#include "State.h"
#include "Subject.h"

namespace dae
{
	class BubbleShotState final : public State, public Subject
	{
	public:
		explicit BubbleShotState(GameObject* owner, Transform* playerTransform);

		~BubbleShotState() override;

		void OnEnter() override;

		void OnExit() override;

		void Update() override;
	private:
		Transform* m_playerTransform{ nullptr }; //The transform of the player that shot this bubble
		glm::vec3 m_initialPlayerPos{};
		glm::vec3 m_playerForward{};
		BubbleComponent* m_bubbleComponent{};
	};
}

