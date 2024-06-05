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


		void ToggleGravity();
		bool IsGravityEnabled() const;
		void SetVerticalVelocity(float verticalVelocity);
		void SetIsJumping(bool jump);
		bool GetIsJumping() const { return m_isJumping; }
	private:
		Transform* m_transform;
		ColliderComponent* m_collider;

		float m_verticalVelocity{};
		bool m_isJumping{};
		float m_fallSpeed{ 9.81f };
		float m_currentFallSpeed{ 0.0f };
		bool m_shouldFall{ true };
		float m_maxSpeed{ 100 };
	};
}
