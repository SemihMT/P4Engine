#pragma once
#include <deque>
#include <vector>

#include "BaseComponent.h"
#include "Text.h"

namespace dae
{
	class FrameCounter : public BaseComponent
	{
	public:
		FrameCounter(const std::shared_ptr<GameObject>& owner);
		~FrameCounter() override = default;

		FrameCounter(const FrameCounter& other) = delete;
		FrameCounter(FrameCounter&& other) = delete;
		FrameCounter& operator=(const FrameCounter& other) = delete;
		FrameCounter& operator=(FrameCounter&& other) = delete;

	public:
		void Update() override;
		void Render() const override;
		float GetFPS() const;
	private:
		double m_lastFrameTime = 0.0;
		std::vector<double> m_frameTimes{60,60};
		float m_fps = 0.0f;
		Text* m_pTextCmp;
		void PrintFPS() const;
	};

}

