#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner, int score) : BaseComponent(owner), m_currentScore(score)
{
}

void dae::ScoreComponent::SetScore(int score)
{
	if (score > 0)
		m_currentScore = score;
}

void dae::ScoreComponent::AddToScore(int scoreToAdd)
{
	if (scoreToAdd > 0)
		m_currentScore += scoreToAdd;
	Notify(Event::Item_Collected,
		{
			.data = {{"Score",m_currentScore},{"Player",GetOwner()}}
		});
}

int dae::ScoreComponent::GetScore() const
{
	return m_currentScore;
}
