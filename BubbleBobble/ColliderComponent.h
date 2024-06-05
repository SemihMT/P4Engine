#pragma once
#include <BaseComponent.h>
#include <SDL_rect.h>
#include <vector>

#include "Transform.h"
#include "Utility.h"

namespace dae
{
	class ColliderComponent final : public BaseComponent
	{
	public:
		enum class CollisionSide { None, Top, Bottom, Left, Right };

		struct CollisionResult
		{
			ColliderComponent* otherCollider;
			CollisionSide collisionSide;
		};

	public:
		ColliderComponent(GameObject* owner, int size, bool isStatic);
		virtual ~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		bool IsColliding(const Collider& other) const;
		void ResolveCollision(const Collider& other);

		bool IsCollidingBottom()const;
		bool IsCollidingTop()const;
		bool IsCollidingLeft()const;
		bool IsCollidingRight()const;
		void SetIsJumping(bool isJumping);
		bool CheckBottomCollision();

	private:

		Transform* m_ownerTransform{};
		bool m_isJumping{};
		Collider m_collider;
		static std::vector<ColliderComponent*> m_colliderComponents;
		bool m_staticCollider{};

		bool m_isCollidingBottom{ false };
		bool m_isCollidingTop{ false };
		bool m_isCollidingLeft{ false };
		bool m_isCollidingRight{ false };

		//Debug vars
		bool m_mouseInRect{ false };
		bool m_rectInRect{ false };

		Ray m_ray{};
		HitResult m_hitResult{};
		bool m_rayInRect{ false };
	};

}
