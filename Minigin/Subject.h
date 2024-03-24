#pragma once
#include <algorithm>
#include <vector>

#include "ObservableEvents.h"
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		virtual void AddObserver(Observer* observer)
		{
			m_pObservers.emplace_back(observer);
		}

		virtual void RemoveObserver(Observer* observer)
		{
			std::erase(m_pObservers, observer);
		}

		virtual void Notify(const Event event, const EventData& data)
		{
			for(const auto& observer : m_pObservers)
			{
				observer->OnNotify(event, data);
			}
		}

	private:
		std::vector<Observer*> m_pObservers{};
	};
}
