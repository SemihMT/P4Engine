#include "FrameCounter.h"

#include <algorithm>

#include "GameObject.h"
#include "Text.h"
#include "TimeManager.h"
using namespace dae;


FrameCounter::FrameCounter(GameObject* owner)
	: BaseComponent(owner),
	  m_pTextCmp(owner->GetComponent<Text>()), m_averageFrameTime(0)
{
}

void FrameCounter::Update()
{
	const double currentTime = TimeManager::GetInstance().TotalTime();
	const double frameTime = TimeManager::GetInstance().DeltaTime();

	// Calculate exponential moving average (EMA) of frame times
	const double alpha = 0.2; // You can adjust this smoothing factor
	if (m_lastFrameTime > 0.0) {
		m_averageFrameTime = alpha * frameTime + (1.0 - alpha) * m_averageFrameTime;
	}
	else {
		m_averageFrameTime = frameTime;
	}

	// Update FPS based on EMA
	m_fps = 1.0f / static_cast<float>(m_averageFrameTime);

	m_lastFrameTime = currentTime;

}

void FrameCounter::Render() const
{
	PrintFPS();
}

float FrameCounter::GetFPS() const
{
	return m_fps;
}

void FrameCounter::PrintFPS() const
{
	// Format FPS with one point of precision
	const std::string fpsText = std::format("{:.1f} FPS - {}s", m_fps, TimeManager::GetInstance().DeltaTime());
	// Update the FPS text component
	m_pTextCmp->SetText(fpsText);
}
