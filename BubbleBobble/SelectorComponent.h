#pragma once
#include <BaseComponent.h>

namespace dae
{
	class SelectorComponent final : public BaseComponent
	{
	public:
		SelectorComponent(GameObject* owner);
		virtual ~SelectorComponent() override = default;

		SelectorComponent(const SelectorComponent& other) = delete;
		SelectorComponent(SelectorComponent&& other) = delete;
		SelectorComponent& operator=(const SelectorComponent& other) = delete;
		SelectorComponent& operator=(SelectorComponent&& other) = delete;

		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;

		void Increment();
		void Decrement();
	private:
		int m_currentSelection{0};
	};
}
