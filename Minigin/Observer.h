#pragma once
namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Event event, const EventData& data) = 0;
	};
}