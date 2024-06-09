#pragma once
#include "BaseComponent.h"
#include "ObservableEvents.h"
#include "Observer.h"

namespace dae
{
	class HealthObserverComponent :public BaseComponent, public Observer
	{
	public:
		HealthObserverComponent(GameObject* owner);
		~HealthObserverComponent() override = default;

		HealthObserverComponent(const HealthObserverComponent& other) = delete;
		HealthObserverComponent(HealthObserverComponent&& other) = delete;
		HealthObserverComponent& operator=(const HealthObserverComponent& other) = delete;
		HealthObserverComponent& operator=(HealthObserverComponent&& other) = delete;

		void OnNotify(Event event, const EventData& data) override;
		void Init(int player1Health,int player2Health);

	private:
		int m_player1Health{ 3 };
		int m_player2Health{ 3 };
	};
}
