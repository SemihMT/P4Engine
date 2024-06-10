#include "MaitaVersusComponent.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthObserverComponent.h"
#include "InputManager.h"
#include "MaitaJumpCommand.h"
#include "MoveCommand.h"
#include "RigidBodyComponent.h"
#include "MaitaShootCommand.h"
#include "PlayerEventHandlerComponent.h"
#include "ScoreComponent.h"
#include "ScoreObserverComponent.h"


dae::MaitaVersusComponent::MaitaVersusComponent(GameObject* owner, const glm::vec3& direction, ColliderType type) :
BaseComponent(owner)
, m_transform(GetOwner()->GetTransform()),
m_spawnPos{GetOwner()->GetTransform()->GetWorldPosition()},
m_spawnDir{direction}
{
	owner->SetName("MaitaVersus");

	owner->AddComponent<AnimationComponent>(m_spritesheetPath);
	owner->GetComponent<AnimationComponent>()->SetDestinationSize(glm::vec2{ static_cast<float>(m_dstSize) });

	int row = 0;
	int numFrames = 2;
	const AnimationData walkAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Walk", walkAnimation);

	row = 1;
	numFrames = 2;
	const AnimationData angryWalkAnimation{ row,numFrames };
	owner->GetComponent<AnimationComponent>()->AddAnimation("AngryWalk", angryWalkAnimation);

	row = 3;
	numFrames = 2;
	const AnimationData bubbleAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Bubble", bubbleAnimation);

	row = 5;
	numFrames = 2;
	const AnimationData angryBubbleAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("AngryBubble", angryBubbleAnimation);

	row = 6;
	numFrames = 4;
	const AnimationData deathAnimation{ row,numFrames,16,0.25f };
	owner->GetComponent<AnimationComponent>()->AddAnimation("Death", deathAnimation);


	auto scoreObserver = SceneManager::GetInstance().GetCurrentScene()->GetGameObject("ScoreObserver");
	owner->AddComponent<ScoreComponent>(0)->AddObserver(scoreObserver->GetComponent<ScoreObserverComponent>());

	auto healthObserver = SceneManager::GetInstance().GetCurrentScene()->GetGameObject("HealthObserver");
	owner->AddComponent<HealthComponent>(3)->AddObserver(healthObserver->GetComponent<HealthObserverComponent>());

	auto observer = owner->AddComponent<PlayerEventHandlerComponent>();
	owner->AddComponent<ColliderComponent>(m_dstSize, type)->AddObserver(observer);
	owner->AddComponent<RigidBodyComponent>();
	owner->AddComponent<StateComponent>();

	

	auto pos = m_transform->GetLocalPosition();
	m_transform->SetLocalPosition(pos.x * static_cast<float>(m_srcSize), pos.y * static_cast<float>(m_srcSize), pos.z);
	m_transform->SetForwardDirection(direction);


	InputManager::GetInstance().AddController();
	InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(owner, glm::vec3{ -1.f, 0.f, 0.f }, m_speed));
	InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(owner, glm::vec3{ 1.f, 0.f, 0.f }, m_speed));
	InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::A, std::make_unique<MaitaJumpCommand>(owner), KeyState::ButtonUp);
	InputManager::GetInstance().BindControllerCommand(Controller::Two, XInputController::Button::B, std::make_unique<MaitaShootCommand>(owner), KeyState::ButtonUp);
}

void dae::MaitaVersusComponent::Shoot()
{
	auto boulder = std::make_unique<GameObject>(m_transform->GetLocalPosition());
	boulder->SetName("Boulder");
	boulder->AddComponent<BoulderComponent>(m_transform->GetForwardDirection());

	SceneManager::GetInstance().GetCurrentScene()->Add(std::move(boulder));
}
