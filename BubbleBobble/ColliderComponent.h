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

		struct CollisionResult {
			ColliderComponent* otherCollider;
			CollisionSide collisionSide;
		};

	public:
		ColliderComponent(GameObject* owner, int size);
		virtual ~ColliderComponent() override = default;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		std::vector<CollisionResult> IsColliding() const;
		bool IsCollidingWith(const ColliderComponent* otherCollider) const;

		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		bool Intersects(const SDL_Rect& other) const;
		CollisionSide GetCollisionSide(const ColliderComponent* other) const;


		Transform* m_ownerTransform{};
		SDL_Rect m_collider;
		bool m_isDirty{ false };
		static std::vector<ColliderComponent*> m_colliderComponents;

	};
	
}
