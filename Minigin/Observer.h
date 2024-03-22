#pragma once
namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify() = 0;
	};
}