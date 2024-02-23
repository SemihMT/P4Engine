#pragma once
#include "BaseComponent.h"
namespace dae
{
	class FrameCounter : public BaseComponent
	{
	public:
		FrameCounter() = default;
		~FrameCounter() override = default;

		FrameCounter(const FrameCounter& other) = delete;
		FrameCounter(FrameCounter&& other) = delete;
		FrameCounter& operator=(const FrameCounter& other) = delete;
		FrameCounter& operator=(FrameCounter&& other) = delete;

	public:
		void Update() override;
		float GetFPS() const;
	private:
		float m_fps{};
		int m_frames{};
		double m_lastFpsTime{};

		void PrintFPS() const;
	};

}

