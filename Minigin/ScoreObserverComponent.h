﻿#pragma once
#include "BaseComponent.h"
#include "ObservableEvents.h"
#include "Observer.h"

namespace dae
{
	class ScoreObserverComponent :public BaseComponent, public Observer
	{

	public:
		ScoreObserverComponent(GameObject* owner);
		~ScoreObserverComponent() override = default;

		ScoreObserverComponent(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent(ScoreObserverComponent&& other) = delete;
		ScoreObserverComponent& operator=(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent& operator=(ScoreObserverComponent&& other) = delete;

		void OnNotify(Event event, const EventData& data) override;

	private:


	};
}
