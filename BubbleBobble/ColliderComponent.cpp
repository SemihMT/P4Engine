#include "ColliderComponent.h"

#include <SDL_render.h>

#include "AddScoreCommand.h"
#include "GameObject.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "TextureComponent.h"

std::vector<dae::ColliderComponent*> dae::ColliderComponent::m_colliderComponents{};

dae::ColliderComponent::ColliderComponent(GameObject* owner, int size, bool isStatic) :
	BaseComponent(owner),
	m_ownerTransform{ owner->GetTransform() },
	m_collider{
		m_ownerTransform->GetWorldPosition(),
		{size,size}
	},
	m_staticCollider{ isStatic }
{
	m_colliderComponents.emplace_back(this);
}

dae::ColliderComponent::~ColliderComponent()
{
	auto it = std::find(m_colliderComponents.begin(), m_colliderComponents.end(), this);
	if (it != m_colliderComponents.end())
	{
		m_colliderComponents.erase(it);
	}
}

void dae::ColliderComponent::Update()
{
	if (m_staticCollider)
		return;

	m_collider.pos = m_ownerTransform->GetWorldPosition();

	Ray bottom{ {m_collider.pos.x + m_collider.size.x / 2.0f,m_collider.pos.y + m_collider.size.y},{0,1} };
	Ray top{ {m_collider.pos.x + m_collider.size.x / 2.0f,m_collider.pos.y},{0,-1} };
	Ray left{ {m_collider.pos.x,m_collider.pos.y + m_collider.size.y / 2},{-1,0} };
	Ray right{ {m_collider.pos.x + m_collider.size.x,m_collider.pos.y + m_collider.size.y / 2},{1,0} };

	bool wasCollidingBottom = false;
	bool wasCollidingTop = false;
	bool wasCollidingLeft = false;
	bool wasCollidingRight = false;

	for (auto component : m_colliderComponents)
	{
		if (component == this)
			continue;

		if (IsColliding(component->m_collider))
		{
			if(component->GetOwner()->GetName() == "ZenChan")
			{
				std::cout << "Colliding with enemy!\n";

			}
			ResolveCollision(component->m_collider);
		}


		HitResult r;
		if (RayVsRect(bottom, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingBottom = true;
		}
		if (RayVsRect(top, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingTop = true;
		}
		if (RayVsRect(left, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingLeft = true;
		}
		if (RayVsRect(right, component->m_collider, r) && r.hitDistance < 1.0f)
		{
			wasCollidingRight = true;
		}
	}

	// Update the collision flags based on whether any collision was detected
	m_isCollidingBottom = wasCollidingBottom;
	m_isCollidingTop = wasCollidingTop;
	m_isCollidingLeft = wasCollidingLeft;
	m_isCollidingRight = wasCollidingRight;



}

void dae::ColliderComponent::Render() const
{
#ifdef NDEBUG
#else
	SDL_FRect colliderRect{ m_collider.pos.x,m_collider.pos.y,m_collider.size.x,m_collider.size.y };
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRectF(Renderer::GetInstance().GetSDLRenderer(), &colliderRect);

	if (!m_staticCollider)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 255, 255);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(), m_collider.pos.x + m_collider.size.x / 2.0f, m_collider.pos.y + m_collider.size.y, m_collider.pos.x + m_collider.size.x / 2.0f, m_collider.pos.y + m_collider.size.y + 1 * 10);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(), m_collider.pos.x + m_collider.size.x / 2.0f, m_collider.pos.y, m_collider.pos.x + m_collider.size.x / 2.0f, m_collider.pos.y + -1 * 10);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(), m_collider.pos.x, m_collider.pos.y + m_collider.size.y / 2, m_collider.pos.x + -1 * 10, m_collider.pos.y + m_collider.size.y / 2);
		SDL_RenderDrawLineF(Renderer::GetInstance().GetSDLRenderer(), m_collider.pos.x + m_collider.size.x, (m_collider.pos.y + m_collider.size.y / 2), m_collider.pos.x + m_collider.size.x + 1 * 10, m_collider.pos.y + m_collider.size.y / 2);
	}
#endif
}

bool dae::ColliderComponent::IsColliding(const Collider& other) const
{
	return (m_collider.pos.x < other.pos.x + other.size.x && m_collider.pos.x + m_collider.size.x > other.pos.x && m_collider.pos.y < other.pos.y + other.size.y && m_collider.pos.y + m_collider.size.y > other.pos.y);
}

void dae::ColliderComponent::ResolveCollision(const Collider& other)
{
	// Calculate the distances to each side of the other collider
	float distanceToLeft = (other.pos.x + other.size.x) - m_collider.pos.x;
	float distanceToRight = (m_collider.pos.x + m_collider.size.x) - other.pos.x;
	float distanceToTop = (other.pos.y + other.size.y) - m_collider.pos.y;
	float distanceToBottom = (m_collider.pos.y + m_collider.size.y) - other.pos.y;

	// Find the closest side
	float minDistance = std::min({ distanceToLeft, distanceToRight, distanceToTop, distanceToBottom });

	// Adjust the position based on the closest side
	if (minDistance == distanceToLeft)
	{
		// Move the collider to the left side
		m_collider.pos.x = other.pos.x + other.size.x;
	}
	else if (minDistance == distanceToRight)
	{
		// Move the collider to the right side
		m_collider.pos.x = other.pos.x - m_collider.size.x;
	}
	else if (minDistance == distanceToTop)
	{
		// Move the collider to the top side
		m_collider.pos.y = other.pos.y + other.size.y;
	}
	else if (minDistance == distanceToBottom)
	{
		// Move the collider to the bottom side
		m_collider.pos.y = other.pos.y - m_collider.size.y;
	}

	m_ownerTransform->SetLocalPosition(glm::vec3{ m_collider.pos,0 });
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

void dae::ColliderComponent::SetIsJumping(bool isJumping)
{
	m_isJumping = isJumping;
}

