#include "ZenChanVulnerableState.h"

#include "StateComponent.h"
#include "TimeManager.h"
#include "ZenChanCalmState.h"

dae::ZenChanVulnerableState::ZenChanVulnerableState(GameObject* owner) :
	State(owner),
	m_animationComponent(GetOwner()->GetComponent<AnimationComponent>())
{
}

dae::ZenChanVulnerableState::~ZenChanVulnerableState()
{
}

void dae::ZenChanVulnerableState::OnEnter()
{
	GetOwner()->SetName("ZenChanBubble");
	m_animationComponent->SetCurrentAnimation("Bubble");
}

void dae::ZenChanVulnerableState::OnExit()
{
}

void dae::ZenChanVulnerableState::Update()
{
	const float dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
	m_respawnTimer += dt;
	if (m_respawnTimer >= m_angryTime)
		m_animationComponent->SetCurrentAnimation("AngryBubble");
	if (m_respawnTimer >= m_maxVulnerableTime)
		GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<ZenChanCalmState>(GetOwner()));

}
