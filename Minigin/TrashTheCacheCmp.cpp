#include "TrashTheCacheCmp.h"

#include <algorithm>
#include <chrono>
#include <numeric>

dae::TrashTheCacheCmp::TrashTheCacheCmp(GameObject* owner) :
BaseComponent(owner)

{
	
}

void dae::TrashTheCacheCmp::InitArrays()
{
	// Initialize array with some values
	for (int i = 0; i < m_bufferSize; ++i) {
		m_intArr[i] = i + 1;
	}
	for (int i = 0; i < m_bufferSize; ++i) {
		m_goArr[i].id = i + 1;
	}
	for (int i = 0; i < m_bufferSize; ++i) {
		m_goArrAlt[i].id = i + 1;
	}
}

void dae::TrashTheCacheCmp::TrashTheCacheEX1()
{
	m_intArr = new int[m_bufferSize];
	for (int i = 0; i < m_bufferSize; ++i) {
		m_intArr[i] = i + 1;
	}
	for (int iteration = 0; iteration < m_iterations; ++iteration) {
		int counter{ 0 };
		// Measure time for each step size
		for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {

			auto start = std::chrono::steady_clock::now();

			for (int i = 0; i < m_bufferSize; i += stepsize) {
				m_intArr[i] *= 2;
			}

			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			//std::cout << "Step size: " << stepsize << ", Time: " << duration << " microseconds" << "\n";
			m_timings[counter].push_back(static_cast<double>(duration / 1000.f));
			++counter;
		}

	}


	// Calculate the average time for each step size
	for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
		// Remove highest and lowest values from each set
		std::vector<double>& setTimings = m_timings[stepsize];
		std::ranges::sort(setTimings);

		// Calculate the average
		double total = std::accumulate(setTimings.begin() + 1, setTimings.end() - 1, 0.0);
		double average = total / (m_iterations - 2);

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


	// Calculate the average time for each step size
	for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
		// Remove highest and lowest values from each set
		std::vector<double>& setTimings = m_goTimings[stepsize];
		std::ranges::sort(setTimings);

		// Calculate the average
		double total = std::accumulate(setTimings.begin() + 1, setTimings.end() - 1, 0.0);
		double average = total / (m_iterations - 2);

		//std::cout << stepsize << "        " << average << "         ms" << "\n";
	}
	delete[] m_goArr;

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


	// Calculate the average time for each step size
	for (int stepsize = 1; stepsize <= m_maxStepSize; stepsize *= 2) {
		// Remove highest and lowest values from each set
		std::vector<double>& setTimings = m_goTimingsAlt[stepsize];
		std::ranges::sort(setTimings);

		// Calculate the average
		double total = std::accumulate(setTimings.begin() + 1, setTimings.end() - 1, 0.0);
		double average = total / (m_iterations - 2);

		//std::cout << stepsize << "        " << average << "         ms" << "\n";
	}

	delete[] m_goArrAlt;
}
