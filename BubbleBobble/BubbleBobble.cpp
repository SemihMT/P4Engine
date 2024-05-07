#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "AnimationComponent.h"
#include "BubbleMovementComponent.h"
#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Components.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "PhysicsComponent.h"
#include "ShootBubble.h"
#include "ShootCommand.h"
#include "SpriteComponent.h"
#include "ToggleSoundCommand.h"
using namespace dae;
void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level 1");
	SceneManager::GetInstance().SetCurrentScene("Level 1");
#pragma region Resources
	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);
#pragma endregion

	auto textObject = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
	textObject->AddComponent<Text>(smallFont, "Press the spacebar or the B button to shoot a bubble!");

	auto bubbleObject = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
	bubbleObject->SetName("Bubble");
	bubbleObject->AddComponent<TextureComponent>("Sprites/Characters/Player/BubSpriteSheet.png");
	bubbleObject->AddComponent<SpriteComponent>(glm::vec2{ 16 }, 3, 3);
	bubbleObject->AddComponent<BubbleMovementComponent>();
	bubbleObject->Disable();


	auto playerObject = std::make_unique<GameObject>(glm::vec3{ 220,240,0 });
	playerObject->AddComponent<TextureComponent>("Sprites/Characters/Player/BubSpriteSheet.png");

	playerObject->AddComponent<AnimationComponent>()->AddAnimation("Walk", { glm::vec2{0,0},{16,16},1,4,4 });
	//playerObject->GetComponent<AnimationComponent>()->SetCurrentAnimation("Walk");

	//addComponent<Physics> -> This component will add a constant downward movement to the player
	//playerObject->AddComponent<PhysicsComponent>();

	//addComponent<Collision> -> This component checks whether an AABB is colliding with other Collision components

	//addComponent<ShootBubble> -> This component interfaces with a bubble object pool when the "ShootCommand" is executed to instantiate a bubble at the player's position
	playerObject->AddComponent<ShootBubble>(bubbleObject.get());
	playerObject->SetName("Player");



	//Player Controls
	const float speed = 100.0f;

	//InputManager::GetInstance().AddController();
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));
	//TODO: Replace the MoveCommand with a proper JumpCommand
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::A, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 25), KeyState::ButtonUp);
	//TODO: This should invoke the ShootCommand 
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