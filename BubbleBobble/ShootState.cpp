#include "ShootState.h"

#include "AnimationComponent.h"
#include "IdleState.h"
#include "ServiceLocator.h"
#include "ShootBubble.h"
#include "StateComponent.h"
#include "TimeManager.h"

dae::ShootState::ShootState(GameObject* owner) : State(owner)
{
}

dae::ShootState::~ShootState()
{
}

void dae::ShootState::OnEnter()
{
	GetOwner()->GetComponent<ShootBubble>()->Shoot();
	ServiceLocator::GetInstance().GetService<ISoundService>("Sound")->PlaySound("ShootBullet.wav");
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("Shoot");
	}
}

void dae::ShootState::OnExit()
{
}

void dae::ShootState::Update()
{
	m_timer += static_cast<float>(TimeManager::GetInstance().DeltaTime());
	if (m_timer >= m_hitDuration)
	{
		std::unique_ptr<State> idleState = std::make_unique<IdleState>(GetOwner());
		GetOwner()->GetComponent<StateComponent>()->SetState(std::move(idleState));
	}
}
