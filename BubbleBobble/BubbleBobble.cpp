#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Components.h"
#include "InputManager.h"
#include "MoveCommand.h"
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

	auto playerObject = std::make_unique<GameObject>(glm::vec3{ 220,240,0 });
	playerObject->AddComponent<Texture>("Sprites/Player.png");
	playerObject->SetName("Player");

	auto bubbleObject = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
	playerObject->SetName("Bubble");
	bubbleObject->AddComponent<Texture>("Sprites/Bubble1.png");
	bubbleObject->Disable();




	const float speed = 100.0f;
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_UP, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_DOWN, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));


	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_DOWN, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(playerObject.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_m, std::make_unique<ToggleSoundCommand>(),KeyState::ButtonUp);


	scene.Add(std::move(playerObject));
	scene.Add(std::move(bubbleObject));

}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}