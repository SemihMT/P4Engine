#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner, int score) : BaseComponent(owner), m_currentScore(score)
{
}

void dae::ScoreComponent::SetScore(int score)
{
	if (score > 0)
		m_currentScore = score;
	Notify(Event::Score_Add,
		{
			.data = {{"Score",m_currentScore},{"Player",GetOwner()}}
		});
}

void dae::ScoreComponent::AddToScore(int scoreToAdd)
{
	if (scoreToAdd > 0)
		m_currentScore += scoreToAdd;
	Notify(Event::Score_Add,
		{
			.data = {{"Score",m_currentScore}, {"Player",GetOwner()}}
		});
	if (m_currentScore >= 500)
		Notify(Event::Score_Win, {});
}

int dae::ScoreComponent::GetScore() const
{
	return m_currentScore;
}
