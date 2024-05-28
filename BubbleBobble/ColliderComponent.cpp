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
	static_cast<int>(m_ownerTransform->GetWorldPosition().x),
	static_cast<int>(m_ownerTransform->GetWorldPosition().y),
	size,
	size
}
{
	m_colliderComponents.emplace_back(this);
}

void dae::ColliderComponent::Update()
{
	m_collider.x = static_cast<int>(m_ownerTransform->GetWorldPosition().x);
	m_collider.y = static_cast<int>(m_ownerTransform->GetWorldPosition().y);

}

void dae::ColliderComponent::Render() const
{
#ifdef NDEBUG
#else
	//render debug
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 1);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_collider);
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
	return Intersects(otherCollider->m_collider);
}

bool dae::ColliderComponent::Intersects(const SDL_Rect& other) const
{
	return SDL_HasIntersection(&m_collider, &other);
}

dae::ColliderComponent::CollisionSide dae::ColliderComponent::GetCollisionSide(const ColliderComponent* other) const
{
	// Determine which side of the collider is colliding with the other collider
	const SDL_Rect otherColliderRect = other->m_collider;

	const float thisCenterX = m_collider.x + m_collider.w / 2.0f;
	const float thisCenterY = m_collider.y + m_collider.h / 2.0f;

	const float otherCenterX = otherColliderRect.x + otherColliderRect.w / 2.0f;
	const float otherCenterY = otherColliderRect.y + otherColliderRect.h / 2.0f;

	if (m_collider.x <= otherColliderRect.x + otherColliderRect.w &&
		m_collider.x + m_collider.w >= otherColliderRect.x &&
		thisCenterY < otherCenterY) {
		return CollisionSide::Bottom;
	}

	if (m_collider.x <= otherColliderRect.x + otherColliderRect.w &&
		m_collider.x + m_collider.w >= otherColliderRect.x &&
		thisCenterY > otherCenterY) {
		return CollisionSide::Top;
	}

	if (m_collider.y <= otherColliderRect.y + otherColliderRect.h &&
		m_collider.y + m_collider.h >= otherColliderRect.y &&
		thisCenterX < otherCenterX) {
		return CollisionSide::Right;
	}

	if (m_collider.y <= otherColliderRect.y + otherColliderRect.h &&
		m_collider.y + m_collider.h >= otherColliderRect.y &&
		thisCenterX > otherCenterX) {
		return CollisionSide::Left;
	}

	return CollisionSide::None;
}


