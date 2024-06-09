#include "MaitaVulnerableState.h"

#include "MaitaChaseState.h"
#include "StateComponent.h"
#include "TimeManager.h"

dae::MaitaVulnerableState::MaitaVulnerableState(GameObject* owner) : State(owner), m_animationComponent(GetOwner()->GetComponent<AnimationComponent>())
{
}

dae::MaitaVulnerableState::~MaitaVulnerableState()
{
}

void dae::MaitaVulnerableState::OnEnter()
{
	GetOwner()->SetName("MaitaBubble");
	m_animationComponent->SetCurrentAnimation("Bubble");
}

void dae::MaitaVulnerableState::OnExit()
{
}

void dae::MaitaVulnerableState::Update()
{
	const float dt = static_cast<float>(TimeManager::GetInstance().DeltaTime());
	m_respawnTimer += dt;
	if (m_respawnTimer >= m_angryTime)
		m_animationComponent->SetCurrentAnimation("AngryBubble");
	if (m_respawnTimer >= m_maxVulnerableTime)
		GetOwner()->GetComponent<StateComponent>()->SetState(std::make_unique<MaitaChaseState>(GetOwner()));
}
