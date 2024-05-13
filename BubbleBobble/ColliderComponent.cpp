#include "ColliderComponent.h"

#include <SDL_render.h>

#include "GameObject.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"

std::vector<dae::ColliderComponent*> dae::ColliderComponent::m_colliderComponents{};

dae::ColliderComponent::ColliderComponent(GameObject* owner, int size) : BaseComponent(owner),
m_ownerTransform{ owner->GetTransform() },
m_collider{
	m_ownerTransform->GetWorldPosition(),
	static_cast<float>(size),
	static_cast<float>(size)
}
{
	m_colliderComponents.emplace_back(this);
}

void dae::ColliderComponent::Update()
{
	m_collider.topLeft = m_ownerTransform->GetWorldPosition();

}

void dae::ColliderComponent::Render() const
{
#ifdef NDEBUG
#else
	//render debug
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 1);
	SDL_Rect collider{};
	collider.w = static_cast<int>(m_collider.width);
	collider.h = static_cast<int>(m_collider.height);
	collider.x = static_cast<int>(m_collider.topLeft.x);
	collider.y = static_cast<int>(m_collider.topLeft.y);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &collider);
#endif


}

std::vector<dae::ColliderComponent::CollisionResult> dae::ColliderComponent::IsColliding() const
{
	std::vector<CollisionResult> collisionResults;
	// Iterate over all other collider components
	for (ColliderComponent* otherCollider : m_colliderComponents) {
		if (otherCollider == this) continue; // skip self

		// Check for collision between this collider and the other collider
		if (IsCollidingWith(otherCollider)) {
			// Determine which sides are colliding
			const CollisionSide collisionSide = GetCollisionSide(otherCollider);

			collisionResults.emplace_back(CollisionResult{ otherCollider, collisionSide });
		}
	}

	return collisionResults;
}

bool dae::ColliderComponent::IsCollidingWith(const ColliderComponent* otherCollider) const
{
	// Simple rectangle collision detection
	return Intersects(otherCollider->m_collider);
}

bool dae::ColliderComponent::Intersects(const Rectangle& other) const
{
	// Check for intersection along both axes (X and Y)
	const bool intersectsX = (m_collider.topLeft.x < other.topLeft.x + other.width) && (m_collider.topLeft.x + m_collider.width > other.topLeft.x);
	const bool intersectsY = (m_collider.topLeft.y > other.topLeft.y - other.height) && (m_collider.topLeft.y - m_collider.height < other.topLeft.y);

	// If both axes have intersection, the rectangles intersect
	return intersectsX && intersectsY;
}

dae::ColliderComponent::CollisionSide dae::ColliderComponent::GetCollisionSide(const ColliderComponent* other) const
{
	// Determine which side of the collider is colliding with the other collider
	const Rectangle otherColliderRect = other->m_collider;

	const float thisCenterX = m_collider.topLeft.x + m_collider.width / 2.0f;
	const float thisCenterY = m_collider.topLeft.y + m_collider.height / 2.0f;

	const float otherCenterX = otherColliderRect.topLeft.x + otherColliderRect.width / 2.0f;
	const float otherCenterY = otherColliderRect.topLeft.y + otherColliderRect.height / 2.0f;

	if (m_collider.topLeft.x <= otherColliderRect.topLeft.x + otherColliderRect.width &&
		m_collider.topLeft.x + m_collider.width >= otherColliderRect.topLeft.x &&
		thisCenterY < otherCenterY) {
		return CollisionSide::Bottom;
	}

	if (m_collider.topLeft.x <= otherColliderRect.topLeft.x + otherColliderRect.width &&
		m_collider.topLeft.x + m_collider.width >= otherColliderRect.topLeft.x &&
		thisCenterY > otherCenterY) {
		return CollisionSide::Top;
	}

	if (m_collider.topLeft.y <= otherColliderRect.topLeft.y + otherColliderRect.height &&
		m_collider.topLeft.y + m_collider.height >= otherColliderRect.topLeft.y &&
		thisCenterX < otherCenterX) {
		return CollisionSide::Right;
	}

	if (m_collider.topLeft.y <= otherColliderRect.topLeft.y + otherColliderRect.height &&
		m_collider.topLeft.y + m_collider.height >= otherColliderRect.topLeft.y &&
		thisCenterX > otherCenterX) {
		return CollisionSide::Left;
	}

	return CollisionSide::None;
}


