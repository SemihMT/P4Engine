#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent : public BaseComponent, public Subject
	{
	public:
		ScoreComponent(GameObject* owner, int score);
		~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void SetScore(int score);
		void AddToScore(int scoreToAdd);
		int GetScore() const;


	private:
		int m_currentScore{};

	};
}
