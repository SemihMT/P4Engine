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
using namespace dae;
void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Week 02");

#pragma region Resources
	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
#pragma endregion

#pragma region BaseScene
	//Linkable AddComponent Calls:
	auto backGroundObject = std::make_unique<GameObject>();
	backGroundObject->AddComponentLinkable<Texture>("background.tga");
	backGroundObject->SetName("BackgroundImage");


	//Default AddComponent Calls:
	auto daeLogoObject = std::make_unique<GameObject>();
	//daeLogoObject->AddComponent<Transform>(); //Adding a component that exists on the same component will return early + log to console
	daeLogoObject->AddComponent<Texture>()->SetTexture("logo.tga");
	daeLogoObject->SetName("DAELogoImage");

	//Getting a Component and modifying its state:
	daeLogoObject->GetComponent<Transform>()->SetLocalPosition(216.0f, 180.0f, 0.0f);

	auto titleObject = std::make_unique<GameObject>();
	titleObject->AddComponentLinkable<Text>(font, "Programming 4 Assignment");
	titleObject->GetComponent<Transform>()->SetLocalPosition(80.0f, 20.0f, 0.0f);
	titleObject->SetName("TitleText");
#pragma endregion

#pragma region Week1
	auto fpsCounterObject = std::make_unique<GameObject>();
	fpsCounterObject
		->AddComponentLinkable<Text>(smallFont, " ")
		->AddComponentLinkable<FrameCounter>();
	fpsCounterObject->SetName("FPSCounter");

#pragma endregion

#pragma region Week2
	/*auto centerObject = std::make_unique<GameObject>(glm::vec3{ 320,240,0 });
	centerObject->SetName("CenterObject");

	auto playerObject = new GameObject();
	playerObject->AddComponent<Texture>("Player.png");
	playerObject->SetParent(centerObject.get(), false);
	playerObject->AddComponent<RotationCmp>(50.f);
	playerObject->SetName("PlayerObject");

	auto bubble1Object = new GameObject();
	bubble1Object->AddComponent<Texture>("Bubble1.png");
	bubble1Object->SetParent(playerObject, false);
	bubble1Object->AddComponent<RotationCmp>(50.f);
	bubble1Object->SetName("Bubble1Object");

	auto bubble2Object = new GameObject();
	bubble2Object->AddComponent<Texture>("Bubble2.png");
	bubble2Object->SetParent(bubble1Object, false);
	bubble2Object->AddComponent<RotationCmp>(60.f);
	bubble2Object->SetName("Bubble2Object");*/

#pragma endregion

#pragma region Week3
	/*auto trashTheCache = std::make_unique<GameObject>(glm::vec3{320,240,0});
	trashTheCache->AddComponent<TrashTheCacheCmp>();
	trashTheCache->SetName("TrashTheCache");*/
#pragma endregion


#pragma region Week4

	auto bubble1Object = std::make_unique<GameObject>(glm::vec3{ 320,240,0 });
	bubble1Object->AddComponent<Texture>("Bubble1.png");
	bubble1Object->SetName("Bubble1Object");

	auto bubble2Object = std::make_unique<GameObject>(glm::vec3{ 220,240,0 });
	bubble2Object->AddComponent<Texture>("Bubble2.png");
	bubble2Object->SetName("Bubble2Object");

	float speed = 100.0f;
	InputManager::GetInstance().BindKeyboardCommand(SDLK_z, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_s, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_q, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_d, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed));

	InputManager::GetInstance().AddController();
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_UP, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_DOWN, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));

	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed*2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_DOWN, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed*2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed*2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed*2));

#pragma endregion
	scene.Add(std::move(backGroundObject));
	scene.Add(std::move(daeLogoObject));
	scene.Add(std::move(titleObject));
	scene.Add(std::move(fpsCounterObject));

	scene.Add(std::move(bubble1Object));
	scene.Add(std::move(bubble2Object));




	//scene.Add(std::move(centerObject));
	////scene.Add(std::move(playerObject));
	//scene.Add(std::move(trashTheCache));





}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}