#pragma once
#include <BaseComponent.h>

#include "ObservableEvents.h"
#include "Observer.h"

namespace dae
{
	class BubbleEventHandlerComponent final : public BaseComponent, public Observer
	{
	public:
		BubbleEventHandlerComponent(GameObject* owner);
		virtual ~BubbleEventHandlerComponent() override = default;

		BubbleEventHandlerComponent(const BubbleEventHandlerComponent& other) = delete;
		BubbleEventHandlerComponent(BubbleEventHandlerComponent&& other) = delete;
		BubbleEventHandlerComponent& operator=(const BubbleEventHandlerComponent& other) = delete;
		BubbleEventHandlerComponent& operator=(BubbleEventHandlerComponent&& other) = delete;

		void OnNotify(Event event, const EventData& data) override;
		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	};
}
