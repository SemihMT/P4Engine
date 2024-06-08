#include "BubblePopState.h"

#include "AnimationComponent.h"
#include "BubbleSpawnState.h"
#include "StateComponent.h"
#include "TimeManager.h"

dae::BubblePopState::BubblePopState(GameObject* owner) : State(owner)
{
}

dae::BubblePopState::~BubblePopState()
{
}

void dae::BubblePopState::OnEnter()
{
	if (const auto animCmp = GetOwner()->GetComponent<AnimationComponent>())
	{
		animCmp->SetCurrentAnimation("BubblePop");
	}
}

void dae::BubblePopState::OnExit()
{
}

void dae::BubblePopState::Update()
{
	const auto dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
	m_popTimer += dt;
	if (m_popTimer >= m_popTime)
	{
		GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<BubbleSpawnState>(GetOwner()));
	}
}
