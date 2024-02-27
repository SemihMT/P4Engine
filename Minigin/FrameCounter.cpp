#include "FrameCounter.h"

#include <algorithm>

#include "GameObject.h"
#include "Text.h"
#include "TimeManager.h"
using namespace dae;


FrameCounter::FrameCounter(const std::shared_ptr<GameObject>& owner)
	: BaseComponent(owner),
	m_pTextCmp(owner->GetComponent<Text>())
{
}

void FrameCounter::Update()
{
	const double currentTime = TimeManager::GetInstance().TotalTime();
	const double frameTime = TimeManager::GetInstance().DeltaTime();

	// Add the frame time to the vector
	m_frameTimes.push_back(frameTime);

	// If we have more than a second's worth of frame times, remove the oldest one
	if (m_frameTimes.size() > 60) {
		m_frameTimes.erase(m_frameTimes.begin());
	}

	// Calculate the median frame time
	std::vector<double> sortedFrameTimes = m_frameTimes;
	std::ranges::sort(sortedFrameTimes);
	const double medianFrameTime = sortedFrameTimes[sortedFrameTimes.size() / 2];

	// Convert the median frame time to FPS
	m_fps = 1.0f / static_cast<float>(medianFrameTime);

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

	m_pTextCmp->SetText(std::to_string((int)m_fps) + " FPS    -   " + std::to_string(TimeManager::GetInstance().DeltaTime()));

}
