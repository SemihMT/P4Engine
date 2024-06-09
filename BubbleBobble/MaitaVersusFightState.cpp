#include "MaitaVersusFightState.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"


dae::MaitaVersusFightState::MaitaVersusFightState(GameObject* owner, const glm::vec3& pos, const glm::vec3& dir) :
	State(owner),
	m_spawnPos(pos),
	m_spawnDir(dir)
{
}

dae::MaitaVersusFightState::~MaitaVersusFightState()
{
}

void dae::MaitaVersusFightState::OnEnter()
{
	GetOwner()->GetTransform()->SetLocalPosition(m_spawnPos);
	GetOwner()->GetTransform()->SetForwardDirection(m_spawnDir);

	if (const auto collider = GetOwner()->GetComponent<ColliderComponent>())
		collider->Enable();
	if (const auto rigidBody = GetOwner()->GetComponent<RigidBodyComponent>())
		rigidBody->Enable();

	GetOwner()->GetComponent<AnimationComponent>()->SetCurrentAnimation("Walk");
}

void dae::MaitaVersusFightState::OnExit()
{
}

void dae::MaitaVersusFightState::Update()
{
}
