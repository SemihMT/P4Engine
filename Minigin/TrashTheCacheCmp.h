#pragma once
#include <vector>

#include "BaseComponent.h"
#include "imgui_impl_opengl3_loader.h"

namespace dae
{
	class TrashTheCacheCmp final : public BaseComponent
	{
	public:
		TrashTheCacheCmp(GameObject* owner);
		~TrashTheCacheCmp() override = default;

		TrashTheCacheCmp(const TrashTheCacheCmp&) = delete;
		TrashTheCacheCmp(TrashTheCacheCmp&&) = delete;
		TrashTheCacheCmp& operator=(const TrashTheCacheCmp&) = delete;
		TrashTheCacheCmp& operator=(TrashTheCacheCmp&&) = delete;

		void RenderImGui() override;
	private:

		class gameobject;
		class gameobjectAlt;

		size_t m_bufferSize{ 1 << 20 };
		int m_iterations{ 100 };

		const size_t m_maxStepSize = 1024;
		std::vector<std::vector<double>> m_timings{ m_maxStepSize + 1 };
		std::vector<std::vector<double>> m_goTimings{ m_maxStepSize + 1 };
		std::vector<std::vector<double>> m_goTimingsAlt{ m_maxStepSize + 1 };
		

		std::vector<float> m_intAvg{};
		std::vector<float> m_goAvg{};
		std::vector<float> m_goAltAvg{};

		int* m_intArr{};
		gameobject* m_goArr{};
		gameobjectAlt* m_goArrAlt{};

		void TrashTheCacheEX1();
		void TrashTheCacheEX2();



		struct transform
		{
			float matrix[16] =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};

		class gameobject
		{
		public:
			transform local;
			int id;
		};

		class gameobjectAlt
		{
		public:
			transform* local;
			int id;
		};

		


	};
}
