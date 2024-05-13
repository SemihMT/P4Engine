#pragma once
#include <BaseComponent.h>
#include <glm/vec3.hpp>


namespace dae
{
	class Transform;
	class BubbleMovementComponent final : public BaseComponent
	{
	public:
		BubbleMovementComponent(GameObject* owner);
		~BubbleMovementComponent() override = default;

		BubbleMovementComponent(const BubbleMovementComponent& other) = delete;
		BubbleMovementComponent(BubbleMovementComponent&& other) = delete;
		BubbleMovementComponent& operator=(const BubbleMovementComponent& other) = delete;
		BubbleMovementComponent& operator=(BubbleMovementComponent&& other) = delete;

		void Update() override;
		void SetMovementDirection(const glm::vec3& dir);
	private:
		Transform* m_transform{ nullptr };
		float m_movementSpeed{ 5.f };
		glm::vec3 m_direction{ 1,0,0 };
	};

}

