#include "FrameCounter.h"

#include "GameObject.h"
#include "Text.h"
#include "TimeManager.h"
using namespace dae;
void FrameCounter::Update()
{

	++m_frames;

	const double elapsedTime = TimeManager::GetInstance().TotalTime() - m_lastFpsTime;

	if (elapsedTime >= 1.0) {
		m_fps = static_cast<float>(m_frames) / static_cast<float>(elapsedTime);
		m_frames = 0;
		m_lastFpsTime = TimeManager::GetInstance().TotalTime();
		PrintFPS();
	}
	
}

float FrameCounter::GetFPS() const
{
	return m_fps;
}

void FrameCounter::PrintFPS() const
{
	if(GetOwner()->GetComponent<Text>())
	{
		GetOwner()->GetComponent<Text>()->SetText(std::to_string(m_fps));
	}
}
