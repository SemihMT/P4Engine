#pragma once
#include <BaseComponent.h>
#include "Transform.h"

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(GameObject* owner, int playerNumber,const glm::vec3& direction, GameObject* bubble);
		virtual ~PlayerComponent() override = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;
		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		Transform* m_transform{ nullptr };
		int m_srcSize{};
		int m_dstSize{ 16 };
		float m_speed{ 64 };
		float m_jumpForce{ 200 };
	};
}
