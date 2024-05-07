#pragma once
#include <BaseComponent.h>

namespace dae
{
	class Transform;
	class PhysicsComponent final : public BaseComponent
	{
	public:
		PhysicsComponent(GameObject* owner);
		virtual ~PhysicsComponent() override = default;

		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
		PhysicsComponent& operator=(PhysicsComponent&& other) = delete;

		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;


		void ToggleGravity();
		bool IsGravityEnabled() const;
	private:
		Transform* m_transform;
		float m_fallSpeed{ 9.81f };
		float m_currentFallSpeed{ 0.0f };
		bool m_shouldFall{ true };
	};
}
