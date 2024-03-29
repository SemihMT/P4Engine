#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "AddScoreCommand.h"
#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Components.h"
#include "DamagePlayerCommand.h"
#include "InputManager.h"
#include "MoveCommand.h"
using namespace dae;
void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Week 02");
	SceneManager::GetInstance().SetCurrentScene("Week 02");
#pragma region Resources
	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);
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

	constexpr int playerMaxLives{ 3 };



	auto tutorialTextP1 = std::make_unique<GameObject>();
	tutorialTextP1->AddComponentLinkable<Text>(smallestFont, "Player 1: ZQSD\nE -> deal damage to p2\nR -> increase score");
	tutorialTextP1->GetComponent<Transform>()->SetLocalPosition(0.0f, 100.0f, 0.0f);
	tutorialTextP1->SetName("TutorialTextP1");

	auto tutorialTextP2 = std::make_unique<GameObject>();
	tutorialTextP2->AddComponentLinkable<Text>(smallestFont, "Player 2: Left stick / D-PAD / Arrow Keys\nR Ctrl/A -> deal damage to p1\nR Alt/B -> increase score");
	tutorialTextP2->GetComponent<Transform>()->SetLocalPosition(0.0f, 145.0f, 0.0f);
	tutorialTextP2->SetName("TutorialTextP2");

	auto lifeDisplay = std::make_unique<GameObject>();
	lifeDisplay->AddComponentLinkable<Text>(smallFont, "# Lives: " + std::to_string(playerMaxLives) + "\n\n# Lives: " + std::to_string(playerMaxLives));
	lifeDisplay->GetComponent<Transform>()->SetLocalPosition(0.0f, 200.0f, 0.0f);
	lifeDisplay->SetName("Lives Display");
	lifeDisplay->AddComponent<HealthObserverComponent>();

	auto pointDisplay = std::make_unique<GameObject>();
	pointDisplay->AddComponentLinkable<Text>(smallFont, "Score: 0\n\nScore: 0");
	pointDisplay->GetComponent<Transform>()->SetLocalPosition(0.0f, 220.0f, 0.0f);
	pointDisplay->SetName("Points Display");
	pointDisplay->AddComponent<ScoreObserverComponent>();

	auto bubble1Object = std::make_unique<GameObject>(glm::vec3{ 320,240,0 });
	bubble1Object->AddComponent<Texture>("Bubble1.png");
	bubble1Object->SetName("Bubble1Object");
	bubble1Object->AddComponent<HealthComponent>(playerMaxLives)->AddObserver(lifeDisplay->GetComponent<HealthObserverComponent>());
	bubble1Object->AddComponent<ScoreComponent>(0)->AddObserver(pointDisplay->GetComponent<ScoreObserverComponent>());

	auto bubble2Object = std::make_unique<GameObject>(glm::vec3{ 220,240,0 });
	bubble2Object->AddComponent<Texture>("Bubble2.png");
	bubble2Object->SetName("Bubble2Object");
	bubble2Object->AddComponent<HealthComponent>(playerMaxLives)->AddObserver(lifeDisplay->GetComponent<HealthObserverComponent>());
	bubble2Object->AddComponent<ScoreComponent>(0)->AddObserver(pointDisplay->GetComponent<ScoreObserverComponent>());



	constexpr float speed = 100.0f;
	InputManager::GetInstance().BindKeyboardCommand(SDLK_z, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_s, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_q, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_d, std::make_unique<MoveCommand>(bubble1Object.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_e, std::make_unique<DamagePlayerCommand>(bubble1Object.get(), bubble2Object.get()), KeyState::ButtonUp);
	InputManager::GetInstance().BindKeyboardCommand(SDLK_r, std::make_unique<AddScoreCommand>(bubble1Object.get()), KeyState::ButtonUp);

	InputManager::GetInstance().AddController();



	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_UP, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_DOWN, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_LEFT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::DPAD_RIGHT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));

	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::LEFT_THUMB, std::make_unique<MoveCommand>(bubble2Object.get(), speed * 2));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::A, std::make_unique<DamagePlayerCommand>(bubble2Object.get(), bubble1Object.get()));
	InputManager::GetInstance().BindControllerCommand(Controller::One, XInputController::Button::B, std::make_unique<AddScoreCommand>(bubble2Object.get()));


	InputManager::GetInstance().BindKeyboardCommand(SDLK_UP, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, -1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_DOWN, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 0.f, 1.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_LEFT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ -1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RIGHT, std::make_unique<MoveCommand>(bubble2Object.get(), glm::vec3{ 1.f, 0.f, 0.f }, speed * 2));
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RCTRL, std::make_unique<DamagePlayerCommand>(bubble2Object.get(), bubble1Object.get()), KeyState::ButtonUp);
	InputManager::GetInstance().BindKeyboardCommand(SDLK_RALT, std::make_unique<AddScoreCommand>(bubble2Object.get()), KeyState::ButtonUp);


#pragma endregion
	scene.Add(std::move(backGroundObject));
	scene.Add(std::move(daeLogoObject));
	scene.Add(std::move(titleObject));
	scene.Add(std::move(fpsCounterObject));

	scene.Add(std::move(bubble1Object));
	scene.Add(std::move(bubble2Object));
	scene.Add(std::move(lifeDisplay));
	scene.Add(std::move(pointDisplay));

	scene.Add(std::move(tutorialTextP1));
	scene.Add(std::move(tutorialTextP2));

}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}