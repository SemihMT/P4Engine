#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "AnimationComponent.h"
#include "BubbleMovementComponent.h"
#include "ColliderComponent.h"
#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Components.h"
#include "IdleState.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "PhysicsComponent.h"
#include "ShootBubble.h"
#include "ShootCommand.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "ToggleSoundCommand.h"
using namespace dae;
void load()
{
#pragma region Resources
	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);
#pragma endregion

	auto& scene = SceneManager::GetInstance().CreateScene("Level 1");
	SceneManager::GetInstance().SetCurrentScene("Level 1");

	auto textObject = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
	textObject->AddComponent<Text>(smallFont, "Press the spacebar or the B button to shoot a bubble!");

	auto bubbleObject = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
	bubbleObject->SetName("Bubble");
	bubbleObject->AddComponent<SpriteComponent>("Sprites/Characters/Player/BubSpriteSheet.png",glm::ivec2{ 16 }, 3, 3, glm::ivec2{ 16 });
	bubbleObject->AddComponent<BubbleMovementComponent>();
	bubbleObject->Disable();


	auto playerObject = std::make_unique<GameObject>(glm::vec3{ 220,240,0 });
	playerObject->AddComponent<AnimationComponent>("Sprites/Characters/Player/BubSpriteSheet.png");
	playerObject->GetComponent<AnimationComponent>()->SetDestinationSize({ 32,32 });

	int row = 0;
	int numFrames = 4;
	const AnimationData walkAnimation{row,numFrames};
	playerObject->GetComponent<AnimationComponent>()->AddAnimation("Walk", walkAnimation);

	row = 0;
	numFrames = 2;
	const AnimationData idleAnimation{row,numFrames};
	playerObject->GetComponent<AnimationComponent>()->AddAnimation("Idle", idleAnimation);

	row = 1;
	numFrames = 4;
	const AnimationData jumpAnimation{row,numFrames};
	playerObject->GetComponent<AnimationComponent>()->AddAnimation("Jump", jumpAnimation);

	playerObject->AddComponent<StateComponent>()->SetState(std::make_unique<IdleState>(playerObject.get()));

	playerObject->AddComponent<ColliderComponent>(32);
	playerObject->AddComponent<PhysicsComponent>();

	playerObject->AddComponent<ShootBubble>(bubbleObject.get());
	playerObject->SetName("Player");



	//Replace with a levelbuilder
	for(int i{}; i < 10; ++i)
	{
		auto tileObject = std::make_unique<GameObject>(glm::vec3{ 220 + i * 32,280,0 });
		tileObject->SetName("Tile");
		tileObject->AddComponent<SpriteComponent>("Sprites/Levels/Tiles/TileMap.png",glm::ivec2{ 8 }, 5, 0, glm::ivec2{ 32 });
		tileObject->AddComponent<ColliderComponent>(32);
		scene.Add(std::move(tileObject));
	}

	for (int i{}; i < 10; ++i)
	{
		auto tileObject = std::make_unique<GameObject>(glm::vec3{ 220 + i * 32,360,0 });
		tileObject->SetName("Tile");
		tileObject->AddComponent<SpriteComponent>("Sprites/Levels/Tiles/TileMap.png",glm::ivec2{ 8 }, 5, 0, glm::ivec2{ 32 });
		tileObject->AddComponent<ColliderComponent>(32);
		scene.Add(std::move(tileObject));
	}

	//Player Controls
	const float speed = 100.0f;

	//InputManager::GetInstance().AddController();
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));
	//TODO: Replace the MoveCommand with a proper JumpCommand
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::A, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 25), KeyState::ButtonUp);
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::B, std::make_unique<ShootCommand>(playerObject.get()), KeyState::ButtonUp);

	InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 25), KeyState::ButtonUp);
	InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, std::make_unique<ShootCommand>(playerObject.get()), KeyState::ButtonUp);

	//Sound Controls
	InputManager::GetInstance().BindKeyboardCommand(SDLK_m, std::make_unique<ToggleSoundCommand>(), KeyState::ButtonUp);


	scene.Add(std::move(playerObject));
	scene.Add(std::move(bubbleObject));
	scene.Add(std::move(textObject));
	

}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}