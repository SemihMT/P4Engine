#include "BoulderComponent.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

dae::BoulderComponent::BoulderComponent(GameObject* owner, const glm::vec2& direction) : BaseComponent(owner),
m_initialPos(GetOwner()->GetTransform()->GetLocalPosition()),
m_direction(direction),
m_speed(75.0f)
{
	owner->AddComponent<AnimationComponent>("/Sprites/Characters/Enemy/MaitaBoulderSheet.png");
	owner->GetComponent<AnimationComponent>()->SetDestinationSize({ m_dstSize,m_dstSize});

	int row = 0;
	int numFrames = 4;
	const AnimationData rollAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Roll", rollAnimation);

	row = 1;
	numFrames = 2;
	const AnimationData crumbleAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Crumble", crumbleAnimation);

	owner->GetComponent<AnimationComponent>()->SetCurrentAnimation("Roll");

	owner->AddComponent<ColliderComponent>(m_dstSize,ColliderType::Trigger);
}

void dae::BoulderComponent::Update()
{
	m_lifetimeTimer += static_cast<float>(TimeManager::GetInstance().DeltaTime());

	if (glm::length(GetOwner()->GetTransform()->GetLocalPosition() - glm::vec3{ m_initialPos,0 }) < m_maxDistance 
		|| m_lifetimeTimer < m_maxLifetime)
	{
		GetOwner()->GetTransform()->Translate(glm::vec3{ m_direction,0 }*m_speed * static_cast<float>(TimeManager::GetInstance().DeltaTime()));
	}
	else
	{
		GetOwner()->Kill();
	}
}
