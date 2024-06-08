#pragma once
#include <BaseComponent.h>
#include <string>

namespace dae
{
	class BubbleComponent final : public BaseComponent
	{
	public:
		BubbleComponent(GameObject* owner, const std::string& spriteSheet);
		virtual ~BubbleComponent() override = default;

		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) = delete;

		bool IsAvailable() const { return m_isAvailable; }
		void SetIsAvailable(bool available) { m_isAvailable = available; }
		float GetSpeed() const { return m_speed; }
		int GetMoveDistance() const { return m_moveDistance; }
		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		bool m_isAvailable{ true };
		int m_srcSize{ 16 };
		int m_dstSize{ 32 };
		float m_speed{ 64.0f };
		int m_moveDistance{ 160 };
		std::string m_spriteSheet{};
	};
}
