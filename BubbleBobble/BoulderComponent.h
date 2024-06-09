#pragma once
#include <BaseComponent.h>
#include <glm/vec2.hpp>

namespace dae
{
	class BoulderComponent final : public BaseComponent
	{
	public:
		BoulderComponent(GameObject* owner, const glm::vec2& direction);
		virtual ~BoulderComponent() override = default;

		BoulderComponent(const BoulderComponent& other) = delete;
		BoulderComponent(BoulderComponent&& other) = delete;
		BoulderComponent& operator=(const BoulderComponent& other) = delete;
		BoulderComponent& operator=(BoulderComponent&& other) = delete;

		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		glm::vec2 m_initialPos{};
		glm::vec2 m_direction{};
		float m_speed{};
		float m_maxDistance{80};
		int m_dstSize{16};
		float m_lifetimeTimer{};
		float m_maxLifetime{10.0f};
	};
}
