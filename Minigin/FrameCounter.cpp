#include "FrameCounter.h"

#include <algorithm>

#include "GameObject.h"
#include "Text.h"
#include "TimeManager.h"
using namespace dae;
void FrameCounter::Update()
{
    double currentTime = TimeManager::GetInstance().TotalTime();
    double frameTime = TimeManager::GetInstance().DeltaTime();

    // Add the frame time to the vector
    m_frameTimes.push_back(frameTime);

    // If we have more than a second's worth of frame times, remove the oldest one
    if (m_frameTimes.size() > m_fps) {
        m_frameTimes.erase(m_frameTimes.begin());
    }

    // Calculate the median frame time
    std::vector<double> sortedFrameTimes = m_frameTimes;
    std::sort(sortedFrameTimes.begin(), sortedFrameTimes.end());
    double medianFrameTime = sortedFrameTimes[sortedFrameTimes.size() / 2];

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
	if(GetOwner()->GetComponent<Text>())
	{
		GetOwner()->GetComponent<Text>()->SetText(std::to_string((int)m_fps) + " FPS    -   " + std::to_string(TimeManager::GetInstance().DeltaTime()));
	}
}
