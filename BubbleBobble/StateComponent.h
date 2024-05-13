#pragma once
#include <BaseComponent.h>

#include "State.h"

namespace dae
{
	class StateComponent final : public BaseComponent
	{
	public:
		StateComponent(GameObject* owner);
		~StateComponent() override = default;

		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;

		void SetState(std::unique_ptr<State> newState);


		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		std::unique_ptr<State> m_currentState{ nullptr };
	};
}
