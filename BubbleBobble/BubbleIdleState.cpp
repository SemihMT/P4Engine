#include "BubbleIdleState.h"

#include "AnimationComponent.h"
#include "BubblePopState.h"
#include "StateComponent.h"
#include "TimeManager.h"

dae::BubbleIdleState::BubbleIdleState(GameObject* owner) : State(owner)
{
}

dae::BubbleIdleState::~BubbleIdleState()
{
}

void dae::BubbleIdleState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubbleIdle");
	}
}

void dae::BubbleIdleState::OnExit()
{
}

void dae::BubbleIdleState::Update()
{
	const auto dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
	const auto t = static_cast<float>(TimeManager::GetInstance().TotalTime());
	GetOwner()->GetTransform()->Translate(0, sinf(t) * .1f, 0);
	m_popTimer += dt;
	if (m_popTimer >= m_popTime)
	{
		GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<BubblePopState>(GetOwner()));
	}
}
