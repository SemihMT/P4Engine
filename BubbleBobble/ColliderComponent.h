#pragma once
#include <BaseComponent.h>
#include <SDL_rect.h>
#include <vector>

#include "GameObject.h"
#include "Subject.h"
#include "Transform.h"
#include "Utility.h"

namespace dae
{
	class ColliderComponent final : public BaseComponent, public Subject
	{
	public:
		explicit ColliderComponent(GameObject* owner, int size, ColliderType type);
		virtual ~ColliderComponent() override;
		void DefineColliderRays(float offset);
		void PerformCollisionTests();

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		bool IsColliding(const Collider& other) const;

		bool IsCollidingBottom()const;
		bool IsCollidingTop()const;
		bool IsCollidingLeft()const;
		bool IsCollidingRight()const;

		bool IsCollidingAllBottom()const;
		bool IsCollidingAllTop()const;
		bool IsCollidingAllLeft()const;
		bool IsCollidingAllRight()const;


		void StartJumping() { m_isInAir = true; }
		void Land() { m_isInAir = false; }
	private:

		void Init();
		void ResolveCollision(ColliderComponent* other);
		void DispatchCollisionEvents(ColliderComponent* other);

		Transform* m_ownerTransform{};
		Collider m_collider;
		static std::vector<ColliderComponent*> m_colliderComponents;

		ColliderType m_type{};
		bool m_isInAir{ false };

		bool m_isCollidingBottom{ false };
		bool m_isCollidingTop{ false };
		bool m_isCollidingLeft{ false };
		bool m_isCollidingRight{ false };

		bool m_isCollidingAllBottom{ false };
		bool m_isCollidingAllTop{ false };
		bool m_isCollidingAllLeft{ false };
		bool m_isCollidingAllRight{ false };

		Ray m_bottomLeft{};
		Ray m_bottomRight{};
		Ray m_topLeft{};
		Ray m_topRight{};
		Ray m_leftBottom{};
		Ray m_leftTop{};
		Ray m_rightBottom{};
		Ray m_rightTop{};

	};

}
