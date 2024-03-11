#include "TrashTheCacheCmp.h"

#include <algorithm>
#include <chrono>
#include <numeric>

#include "imgui.h"
#include "implot.h"

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
		//Create ImGui Window
		ImGui::Begin("Ex 1");

		//Add a button to it
		if (ImGui::Button("Trash the cache!"))
		{
			//Trash the cache if button gets pressed
			m_showPlotEx1 = TrashTheCacheEX1();
		}
		//Find the max y value we need to show on the graph
		const auto max = std::max_element(m_intAvg.begin(), m_intAvg.end());
		const char* labels[]{ "1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024" }; //custom X axis labels
		std::vector<double> val{ 0,1,2,3,4,5,6,7,8,9,10 }; // defining at what location the labels get shown on the x axis
		
		if (m_showPlotEx1 && ImPlot::BeginPlot("Exercise 1", ImVec2(-1, 0), ImPlotFlags_NoMouseText | ImPlotFlags_Crosshairs | ImPlotFlags_NoInputs))
		{

			ImPlot::SetupAxes("Stepsize", "Time in ms");
			ImPlot::SetupAxesLimits(0, 10, 0, *max + 1);
			ImPlot::SetupAxisTicks(ImAxis_X1, val.data(), static_cast<int>(val.size()), labels, false);

			ImPlot::PlotLine("Timings", m_intAvg.data(), static_cast<int>(m_intAvg.size()));

			ImPlot::EndPlot();

		}
		ImGui::End();
	}

	{
		ImGui::Begin("Ex 2");
		if (ImGui::Button("Trash the cache!"))
		{
			m_showPlotEx2 = TrashTheCacheEX2();
		}
		const auto maxGo = std::ranges::max_element(m_goAvg);
		const auto maxGoAlt = std::ranges::max_element(m_goAltAvg);

		const char* labels[]{ "1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024" };
		std::vector<double> val{ 0,1,2,3,4,5,6,7,8,9,10 };


		if (m_showPlotEx2 && ImPlot::BeginPlot("Exercise 2", ImVec2(-1, 0), ImPlotFlags_NoMouseText | ImPlotFlags_Crosshairs | ImPlotFlags_NoInputs))
		{

			ImPlot::SetupAxes("Stepsize", "Time in ms");
			ImPlot::SetupAxesLimits(0, 10, 0, *maxGo + 1);
			ImPlot::SetupAxisTicks(ImAxis_X1, val.data(), static_cast<int>(val.size()), labels, false);

			ImPlot::PlotLine("Timings GameObject", m_goAvg.data(), (int)m_goAvg.size());

			ImPlot::EndPlot();
		}
		if (m_showPlotEx2 && ImPlot::BeginPlot("Exercise 2a", ImVec2(-1, 0), ImPlotFlags_NoMouseText | ImPlotFlags_Crosshairs | ImPlotFlags_NoInputs))
		{
			ImPlot::SetupAxes("Stepsize", "Time in ms");
			ImPlot::SetupAxesLimits(0, 10, 0, *maxGoAlt + 1);
			ImPlot::SetupAxisTicks(ImAxis_X1, val.data(), static_cast<int>(val.size()), labels, false);

			ImPlot::PlotLine("Timings GameObjectAlt", m_goAltAvg.data(), static_cast<int>(m_goAltAvg.size()));

			ImPlot::EndPlot();
		}

		if (m_showPlotEx2 && ImPlot::BeginPlot("Combined", ImVec2(-1, 0), ImPlotFlags_NoMouseText | ImPlotFlags_Crosshairs | ImPlotFlags_NoInputs))
		{
			ImPlot::SetupAxes("Stepsize", "Time in ms");
			ImPlot::SetupAxesLimits(0, 10, 0, *maxGo + 1);
			ImPlot::SetupAxisTicks(ImAxis_X1, val.data(), static_cast<int>(val.size()), labels, false);

			ImPlot::PlotLine("Timings GameObject", m_goAvg.data(), (int)m_goAvg.size());
			ImPlot::PlotLine("Timings GameObjectAlt", m_goAltAvg.data(), static_cast<int>(m_goAltAvg.size()));

			ImPlot::EndPlot();
		}

		ImGui::End();
	}

}

bool dae::TrashTheCacheCmp::TrashTheCacheEX1()
{
	m_intArr = new int[m_bufferSize];
	for (int i = 0; i < m_bufferSize; ++i) {
		m_intArr[i] = i + 1;
	}
	for (int iteration = 0; iteration < m_iterations; ++iteration) {
		// Measure time for each step size
		for (int stepsize = 1; stepsize <= static_cast<int>(m_maxStepSize); stepsize *= 2) {

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
	for (int stepsize = 1; stepsize <= static_cast<int>(m_maxStepSize); stepsize *= 2) {
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
	return true;


}

bool dae::TrashTheCacheCmp::TrashTheCacheEX2()
{

	m_goArr = new gameobject[m_bufferSize];
	for (int i = 0; i < m_bufferSize; ++i) {
		m_goArr[i].id = i + 1;
	}


	for (int iteration = 0; iteration < m_iterations; ++iteration) {
		// Measure time for each step size
		for (int stepsize = 1; stepsize <= static_cast<int>(m_maxStepSize); stepsize *= 2) {
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
	for (int stepsize = 1; stepsize <= static_cast<int>(m_maxStepSize); stepsize *= 2) {
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
		for (int stepsize = 1; stepsize <= static_cast<int>(m_maxStepSize); stepsize *= 2) {
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
	for (int stepsize = 1; stepsize <= static_cast<int>(m_maxStepSize); stepsize *= 2) {
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
	return true;
}
