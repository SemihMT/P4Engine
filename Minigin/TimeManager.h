#pragma once
#include <chrono>

#include "Singleton.h"


namespace dae
{
	class TimeManager final : public Singleton<TimeManager>
	{
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	public:
		void Update();
		TimePoint Current() const;
		double DeltaTime() const;
		double TotalTime() const;
		double FrameTime() const;
		void SetFrameTime(int preferredFPS);

	private:
		friend class Singleton<TimeManager>;
		TimeManager() = default;

		double m_deltaTime{ 0 };
		double m_totalTime{ 0 };
		double m_frameTime{ 1.0 / 60 };

		TimePoint m_currentFrameTime = std::chrono::high_resolution_clock::now();
		TimePoint m_lastFrameTime = std::chrono::high_resolution_clock::now();
	};
}


