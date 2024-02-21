#pragma once
#include "Singleton.h"


namespace dae
{
	class TimeManager final : public Singleton<TimeManager>
	{
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	public:
		void Update()
		{
			m_CurrentFrameTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = m_CurrentFrameTime - m_LastFrameTime;
			m_DeltaTime = duration.count();
			m_TotalTime += m_DeltaTime;
			m_LastFrameTime = m_CurrentFrameTime;
		}
		TimePoint Current() { return m_CurrentFrameTime; }
		double DeltaTime() { return m_DeltaTime; };
		double TotalTime() { return m_TotalTime; };
		double FrameTime() { return m_FrameTime; };
		void SetFrameTime(int preferredFPS) { m_FrameTime = 1.0 / preferredFPS; };
	private:
		friend class Singleton<TimeManager>;
		TimeManager() = default;

		double m_DeltaTime{ 0 };
		double m_TotalTime{ 0 };
		double m_FrameTime{ 1.0 / 60 };

		TimePoint m_CurrentFrameTime = std::chrono::high_resolution_clock::now();
		TimePoint m_LastFrameTime = std::chrono::high_resolution_clock::now();
	};
}


