#pragma once
#include <BaseComponent.h>

#include "ColliderComponent.h"

namespace dae
{
	class Transform;
	class RigidBodyComponent final : public BaseComponent
	{
	public:
		RigidBodyComponent(GameObject* owner);
		virtual ~RigidBodyComponent() override = default;

		RigidBodyComponent(const RigidBodyComponent& other) = delete;
		RigidBodyComponent(RigidBodyComponent&& other) = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&& other) = delete;

		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
		void Jump();
		float GetVerticalVelocity() const { return m_verticalVelocity; }
	private:
		Transform* m_transform;
		ColliderComponent* m_collider;
		bool m_shouldFall{ false };
		bool m_isJumping{ false };
		float m_verticalVelocity{ 0.0f };

		float m_gravity{ 200.f };
		float m_horizontalAirControlForce{ 50.0f };
		float m_idleAirForce{ 100.0f };
		float m_jumpVelocity{ -170.0 };
	};
}
