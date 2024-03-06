#include "TrashTheCacheCmp.h"

#include <algorithm>
#include <chrono>
#include <numeric>

#include "imgui.h"

dae::TrashTheCacheCmp::TrashTheCacheCmp(GameObject* owner) :
BaseComponent(owner)

{
	m_intAvg.resize(11);
	m_goAvg.resize(11);
	m_goAltAvg.resize(11);
}

void dae::TrashTheCacheCmp::RenderImGui() 
{
	{
		ImGui::Begin("Ex 1");
		if (ImGui::Button("Trash the cache!"))
		{
			TrashTheCacheEX1();
		}
		auto max = std::max_element(m_intAvg.begin(), m_intAvg.end());
		ImGui::PlotLines("Timings", m_intAvg.data(), static_cast<int>(m_intAvg.size()), 0, nullptr, 0.0f, *max + 1, ImVec2(200, 200));
		ImGui::End();
	}

	{
		ImGui::Begin("Ex 2");
		if (ImGui::Button("Trash the cache!"))
		{
			TrashTheCacheEX2();
		}
		auto maxGo = std::max_element(m_goAvg.begin(), m_goAvg.end());
		auto maxGoAlt = std::max_element(m_goAltAvg.begin(), m_goAltAvg.end());
		ImGui::PlotLines("Timings GameObject", m_goAvg.data(), static_cast<int>(m_goAvg.size()), 0, nullptr, 0.0f, *maxGo + 1, ImVec2(200, 200));
		ImGui::PlotLines("Timings GameObjectAlt", m_goAltAvg.data(), static_cast<int>(m_goAltAvg.size()), 0, nullptr, 0.0f, *maxGoAlt + 1, ImVec2(200, 200));


		ImGui::PlotLines("Combined", m_goAvg.data(), static_cast<int>(m_goAvg.size()), 0, nullptr, 0.0f, *maxGo + 1, ImVec2(200, 200));

		//AI-generated code from here ↓
		//Couldn't find any resources regarding drawing two datasets on one graph using pure ImGui
		//Should probably have added ImPlot...
		//ImDrawList* drawList = ImGui::GetWindowDrawList();
		//ImVec2 graph_min = ImGui::GetItemRectMin();
		//ImVec2 graph_max = ImGui::GetItemRectMax();

		//// Find the maximum and minimum values in m_goAltAvg
		//float max_value = *std::max_element(m_goAltAvg.begin(), m_goAltAvg.end());
		//float min_value = *std::min_element(m_goAltAvg.begin(), m_goAltAvg.end());

		//
		//for (int i = 1; i < m_goAltAvg.size(); i++)
		//{
		//	// Normalize the values to [0, 1]
		//	float normalized_prev = (m_goAltAvg[i - 1] - min_value) / (max_value - min_value);
		//	float normalized_curr = (m_goAltAvg[i] - min_value) / (max_value - min_value);

		//	drawList->AddLine(
		//		ImVec2(graph_min.x + (i - 1) / (float)(m_goAltAvg.size() - 1) * (graph_max.x - graph_min.x), graph_min.y + (1.0f - normalized_prev) * (graph_max.y - graph_min.y)),
		//		ImVec2(graph_min.x + i / (float)(m_goAltAvg.size() - 1) * (graph_max.x - graph_min.x), graph_min.y + (1.0f - normalized_curr) * (graph_max.y - graph_min.y)),
		//		IM_COL32(255, 0, 0, 255)  // Red color
		//	);
		//}


		ImGui::End();
	}

}

void dae::TrashTheCacheCmp::TrashTheCacheEX1()
{
	m_intArr = new int[m_bufferSize];
	for (int i = 0; i < m_bufferSize; ++i) {
		m_intArr[i] = i + 1;
	}
	for (int iteration = 0; iteration < m_iterations; ++iteration) {
		// Measure time for each step size
		for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {

			auto start = std::chrono::steady_clock::now();

			for (int i = 0; i < m_bufferSize; i += stepsize) {
				m_intArr[i] *= 2;
			}

			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			//std::cout << "Step size: " << stepsize << ", Time: " << duration << " microseconds" << "\n";
			m_timings[stepsize].push_back(static_cast<double>(duration / 1000.f));
		}

	}

	int counter{ 0 };
	// Calculate the average time for each step size
	for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
		// Remove highest and lowest values from each set
		std::vector<double>& setTimings = m_timings[stepsize];
		std::ranges::sort(setTimings);

		// Calculate the average
		double total = std::accumulate(setTimings.begin() + 1, setTimings.end() - 1, 0.0);
		double average = total / (m_iterations - 2);
		m_intAvg[counter] = static_cast<float>(average);
		++counter;

		//std::cout << stepsize << "        " << average << "         ms" << "\n";
	}
	delete[] m_intArr;

	

}

void dae::TrashTheCacheCmp::TrashTheCacheEX2()
{

	m_goArr = new gameobject[m_bufferSize];
	for (int i = 0; i < m_bufferSize; ++i) {
		m_goArr[i].id = i + 1;
	}
	

	for (int iteration = 0; iteration < m_iterations; ++iteration) {
		// Measure time for each step size
		for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
			auto start = std::chrono::steady_clock::now();

			for (int i = 0; i < m_bufferSize; i += stepsize) {
				m_goArr[i].id *= 2;
			}

			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			//std::cout << "Step size: " << stepsize << ", Time: " << duration << " microseconds" << "\n";
			m_goTimings[stepsize].push_back(static_cast<double>(duration / 1000.f));
		}
	}

	int counter{ 0 };
	// Calculate the average time for each step size
	for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
		// Remove highest and lowest values from each set
		std::vector<double>& setTimings = m_goTimings[stepsize];
		std::ranges::sort(setTimings);

		// Calculate the average
		double total = std::accumulate(setTimings.begin() + 1, setTimings.end() - 1, 0.0);
		double average = total / (m_iterations - 2);

		//std::cout << stepsize << "        " << average << "         ms" << "\n";
		m_goAvg[counter] = static_cast<float>(average);
		++counter;
	}
	delete[] m_goArr;

	m_goArrAlt = new gameobjectAlt[m_bufferSize];
	for (int i = 0; i < m_bufferSize; ++i) {
		m_goArrAlt[i].id = i + 1;
	}

	for (int iteration = 0; iteration < m_iterations; ++iteration) {
		// Measure time for each step size
		for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
			auto start = std::chrono::steady_clock::now();

			for (int i = 0; i < m_bufferSize; i += stepsize) {
				m_goArrAlt[i].id *= 2;
			}

			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			//std::cout << "Step size: " << stepsize << ", Time: " << duration << " microseconds" << "\n";
			m_goTimingsAlt[stepsize].push_back(static_cast<double>(duration / 1000.f));
		}
	}

	counter = 0;
	// Calculate the average time for each step size
	for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
		// Remove highest and lowest values from each set
		std::vector<double>& setTimings = m_goTimingsAlt[stepsize];
		std::ranges::sort(setTimings);

		// Calculate the average
		double total = std::accumulate(setTimings.begin() + 1, setTimings.end() - 1, 0.0);
		double average = total / (m_iterations - 2);

		//std::cout << stepsize << "        " << average << "         ms" << "\n";

		m_goAltAvg[counter] = static_cast<float>(average);
		++counter;
	}

	delete[] m_goArrAlt;
}
