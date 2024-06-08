#include "ColliderComponent.h"

#include <SDL_render.h>

#include "AddScoreCommand.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "PlayerEventHandlerComponent.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "TextureComponent.h"

std::vector<dae::ColliderComponent*> dae::ColliderComponent::m_colliderComponents{};

dae::ColliderComponent::ColliderComponent(GameObject* owner, int size, ColliderType type) :
	BaseComponent(owner),
	m_ownerTransform{ owner->GetTransform() },
	m_collider{
		m_ownerTransform->GetWorldPosition(),
		{size,size}
	},
	m_type{ type }
{
	m_colliderComponents.emplace_back(this);

}

dae::ColliderComponent::~ColliderComponent()
{
	const auto it = std::ranges::find(m_colliderComponents, this);
	if (it != m_colliderComponents.end())
	{
		m_colliderComponents.erase(it);
	}
}


void dae::ColliderComponent::Update()
{
	// No need to do collision checks for non-dynamic colliders
	if (m_type == ColliderType::Wall || m_type == ColliderType::Platform)
		return;

	m_collider.pos = m_ownerTransform->GetWorldPosition();

	// Define an offset to place rays closer together
	constexpr float offset = 2.0f;
	DefineColliderRays(offset);

	//Check if this collider collides with any other in the scene
	PerformCollisionTests();
}

void dae::ColliderComponent::Render() const
{
#ifdef NDEBUG
#else
	SDL_FRect colliderRect{ m_collider.pos.x,m_collider.pos.y,m_collider.size.x,m_collider.size.y };
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRectF(Renderer::GetInstance().GetSDLRenderer(), &colliderRect);

	//Render the raycast rays we're using for the collision checks
	if (!(m_type == ColliderType::Wall || m_type == ColliderType::Platform))
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 255, 255);

		// Draw bottom rays
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_bottomLeft.origin.x, m_bottomLeft.origin.y,
			m_bottomLeft.origin.x + m_bottomLeft.direction.x * 10, m_bottomLeft.origin.y + m_bottomLeft.direction.y * 10);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_bottomRight.origin.x, m_bottomRight.origin.y,
			m_bottomRight.origin.x + m_bottomRight.direction.x * 10, m_bottomRight.origin.y + m_bottomRight.direction.y * 10);

		// Draw top rays
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_topLeft.origin.x, m_topLeft.origin.y,
			m_topLeft.origin.x + m_topLeft.direction.x * 10, m_topLeft.origin.y + m_topLeft.direction.y * 10);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_topRight.origin.x, m_topRight.origin.y,
			m_topRight.origin.x + m_topRight.direction.x * 10, m_topRight.origin.y + m_topRight.direction.y * 10);

		// Draw left rays
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_leftBottom.origin.x, m_leftBottom.origin.y,
			m_leftBottom.origin.x + m_leftBottom.direction.x * 10, m_leftBottom.origin.y + m_leftBottom.direction.y * 10);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_leftTop.origin.x, m_leftTop.origin.y,
			m_leftTop.origin.x + m_leftTop.direction.x * 10, m_leftTop.origin.y + m_leftTop.direction.y * 10);

		// Draw right rays
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_rightBottom.origin.x, m_rightBottom.origin.y,
			m_rightBottom.origin.x + m_rightBottom.direction.x * 10, m_rightBottom.origin.y + m_rightBottom.direction.y * 10);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(),
			m_rightTop.origin.x, m_rightTop.origin.y,
			m_rightTop.origin.x + m_rightTop.direction.x * 10, m_rightTop.origin.y + m_rightTop.direction.y * 10);
	}
#endif
}



void dae::ColliderComponent::DefineColliderRays(float offset)
{
	// Define rays for each side, closer to the center
	m_bottomLeft = { {m_collider.pos.x + offset, m_collider.pos.y + m_collider.size.y}, {0, 1} };
	m_bottomRight = { {m_collider.pos.x + m_collider.size.x - offset, m_collider.pos.y + m_collider.size.y}, {0, 1} };
	m_topLeft = { {m_collider.pos.x + offset, m_collider.pos.y}, {0, -1} };
	m_topRight = { {m_collider.pos.x + m_collider.size.x - offset, m_collider.pos.y}, {0, -1} };
	m_leftBottom = { {m_collider.pos.x, m_collider.pos.y + m_collider.size.y - offset}, {-1, 0} };
	m_leftTop = { {m_collider.pos.x, m_collider.pos.y + offset}, {-1, 0} };
	m_rightBottom = { {m_collider.pos.x + m_collider.size.x, m_collider.pos.y + m_collider.size.y - offset}, {1, 0} };
	m_rightTop = { {m_collider.pos.x + m_collider.size.x, m_collider.pos.y + offset}, {1, 0} };
}

void dae::ColliderComponent::PerformCollisionTests()
{
	bool wasCollidingBottomLeft = false;
	bool wasCollidingBottomRight = false;
	bool wasCollidingTopLeft = false;
	bool wasCollidingTopRight = false;
	bool wasCollidingLeftBottom = false;
	bool wasCollidingLeftTop = false;
	bool wasCollidingRightBottom = false;
	bool wasCollidingRightTop = false;

	for (const auto component : m_colliderComponents)
	{
		if (component == this)
			continue;


		if (IsColliding(component->m_collider))
		{

			DispatchCollisionEvents(component);

			ResolveCollision(component);
		}


		if (component->m_type == ColliderType::Trigger)
			continue;
		HitResult r;

		// Check collisions for each ray
		if (RayVsRect(m_bottomLeft, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingBottomLeft = true;
		}
		if (RayVsRect(m_bottomRight, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingBottomRight = true;
		}
		if (RayVsRect(m_topLeft, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingTopLeft = true;
		}
		if (RayVsRect(m_topRight, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingTopRight = true;
		}
		if (RayVsRect(m_leftBottom, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingLeftBottom = true;
		}
		if (RayVsRect(m_leftTop, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingLeftTop = true;
		}
		if (RayVsRect(m_rightBottom, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingRightBottom = true;
		}
		if (RayVsRect(m_rightTop, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingRightTop = true;
		}
	}

	// Update the collision flags based on whether any collision was detected
	m_isCollidingBottom = wasCollidingBottomLeft || wasCollidingBottomRight;
	m_isCollidingTop = wasCollidingTopLeft || wasCollidingTopRight;
	m_isCollidingLeft = wasCollidingLeftBottom || wasCollidingLeftTop;
	m_isCollidingRight = wasCollidingRightBottom || wasCollidingRightTop;

	// Update the both collision flags
	m_isCollidingAllBottom = wasCollidingBottomLeft && wasCollidingBottomRight;
	m_isCollidingAllTop = wasCollidingTopLeft && wasCollidingTopRight;
	m_isCollidingAllLeft = wasCollidingLeftBottom && wasCollidingLeftTop;
	m_isCollidingAllRight = wasCollidingRightBottom && wasCollidingRightTop;
}


bool dae::ColliderComponent::IsColliding(const Collider& other) const
{
	return (m_collider.pos.x < other.pos.x + other.size.x && m_collider.pos.x + m_collider.size.x > other.pos.x && m_collider.pos.y < other.pos.y + other.size.y && m_collider.pos.y + m_collider.size.y > other.pos.y);
}

void dae::ColliderComponent::ResolveCollision(ColliderComponent* other)
{
	auto otherCollider = other->m_collider;
	// Calculate the overlap on each side
	float overlapLeft = m_collider.pos.x + m_collider.size.x - otherCollider.pos.x;
	float overlapRight = otherCollider.pos.x + otherCollider.size.x - m_collider.pos.x;
	float overlapTop = m_collider.pos.y + m_collider.size.y - otherCollider.pos.y;
	float overlapBottom = otherCollider.pos.y + otherCollider.size.y - m_collider.pos.y;

	// Check if the colliders are actually overlapping
	if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
	{
		// Check if we're in the air and the collision is with a platform tile
		if (m_isInAir && other->m_type == ColliderType::Platform)
		{
			// Ignore the collision
			return;
		}
		if (other->m_type == ColliderType::Trigger)
		{
			return;
		}

		// Find the smallest overlap
		float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

		// Adjust the position based on the smallest overlap
		if (minOverlap == overlapLeft)
		{
			// Move the collider to the left
			m_collider.pos.x = otherCollider.pos.x - m_collider.size.x - 1;
		}
		else if (minOverlap == overlapRight)
		{
			// Move the collider to the right
			m_collider.pos.x = otherCollider.pos.x + otherCollider.size.x + 1;
		}
		else if (minOverlap == overlapTop)
		{
			// Move the collider to the top
			m_collider.pos.y = otherCollider.pos.y - m_collider.size.y - 1;
		}
		else if (minOverlap == overlapBottom)
		{
			// Move the collider to the bottom
			m_collider.pos.y = otherCollider.pos.y + otherCollider.size.y + 1;
		}

		// Update the position of the owner transform
		m_ownerTransform->SetLocalPosition(glm::vec3{ m_collider.pos, 0 });
	}
}

void dae::ColliderComponent::DispatchCollisionEvents(ColliderComponent* other)
{
	const auto ourName = GetOwner()->GetName();
	const auto otherName = other->GetOwner()->GetName();

	if (ourName == "Player")
	{
		// Touches free enemy / their projectiles
		if (otherName == "ZenChan"
			|| otherName == "Maita"
			|| otherName == "MaitaBoulder")
		{
			EventData d{};
			d.data["PlayerNumber"] = GetOwner()->GetComponent<PlayerComponent>()->GetPlayerNumber();
			Notify(Event::Player_Damaged, d);
		}


		if (otherName == "ZenChanBubble"
			|| otherName == "MaitaBubble")
		{
			//Store the enemy we've hit, so we can modify its state
			EventData data{};
			data.data["PoppedEnemy"] = other->GetOwner();
			Notify(Event::Bubble_PopEnemy, { data });
		}
	}

	if (ourName == "Bubble")
	{
		// Bubble touches free enemy 
		if (otherName == "ZenChan"
			|| otherName == "Maita")
		{
			//Store the enemy we've hit, so we can modify its state
			EventData data{};
			data.data["HitEnemy"] = other->GetOwner();
			Notify(Event::Bubble_HitEnemy, data);

		}

		if (otherName == "Player")
		{
			// Assume that if we're colliding with the player && something is touching the top side of the collider
			// It's the player
			if (IsCollidingTop())
			{
				EventData data{};
				data.data["Player"] = other->GetOwner();
				Notify(Event::Bubble_PlayerJump, data);
			}
			else
			{
				Notify(Event::Bubble_PopNoEnemy, {});
			}
		}
	}

}

bool dae::ColliderComponent::IsCollidingBottom() const
{
	return m_isCollidingBottom;
}

bool dae::ColliderComponent::IsCollidingTop() const
{
	return m_isCollidingTop;
}

bool dae::ColliderComponent::IsCollidingLeft() const
{
	return m_isCollidingLeft;
}

bool dae::ColliderComponent::IsCollidingRight() const
{
	return m_isCollidingRight;
}

bool dae::ColliderComponent::IsCollidingAllBottom() const
{
	return m_isCollidingAllBottom;
}

bool dae::ColliderComponent::IsCollidingAllTop() const
{
	return m_isCollidingAllTop;
}

bool dae::ColliderComponent::IsCollidingAllLeft() const
{
	return m_isCollidingAllLeft;
}

bool dae::ColliderComponent::IsCollidingAllRight() const
{
	return m_isCollidingAllRight;
}

void dae::ColliderComponent::Init()
{
}
