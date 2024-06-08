#pragma once
#include <BaseComponent.h>

#include "ObservableEvents.h"
#include "Observer.h"

namespace dae
{
	class PlayerEventHandlerComponent final : public BaseComponent, public Observer
	{
	public:
		PlayerEventHandlerComponent(GameObject* owner);
		virtual ~PlayerEventHandlerComponent() override = default;

		PlayerEventHandlerComponent(const PlayerEventHandlerComponent& other) = delete;
		PlayerEventHandlerComponent(PlayerEventHandlerComponent&& other) = delete;
		PlayerEventHandlerComponent& operator=(const PlayerEventHandlerComponent& other) = delete;
		PlayerEventHandlerComponent& operator=(PlayerEventHandlerComponent&& other) = delete;

		void OnNotify(Event event, const EventData& data) override;
		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		void UnbindAllControls(int playerNumber);
		void BindAllControls(int playerNumber);
	};
}
