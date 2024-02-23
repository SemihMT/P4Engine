#include "TimeManager.h"

void dae::TimeManager::Update()
{
	m_currentFrameTime = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> duration = m_currentFrameTime - m_lastFrameTime;
	m_deltaTime = duration.count();
	m_totalTime += m_deltaTime;
	m_lastFrameTime = m_currentFrameTime;
}

dae::TimeManager::TimePoint dae::TimeManager::Current() const
{
	return m_currentFrameTime;
}

double dae::TimeManager::DeltaTime() const
{
	return m_deltaTime;
}

double dae::TimeManager::TotalTime() const
{
	return m_totalTime;
}

double dae::TimeManager::FrameTime() const
{
	return m_frameTime;
}

void dae::TimeManager::SetFrameTime(int preferredFPS)
{
	m_frameTime = 1.0 / preferredFPS;
}
