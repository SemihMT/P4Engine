#pragma once
#include <BaseComponent.h>


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
	private:
		Transform* m_pTransform{ nullptr };
		float m_movementSpeed{ 5.f };
		
	};

}

