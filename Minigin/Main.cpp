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
using namespace dae;
void load()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Week 02");
#pragma region BaseScene
	//Linkable AddComponent Calls:
	auto backGroundObject = std::make_unique<GameObject>();
	backGroundObject->AddComponentLinkable<Texture>("background.tga");

	//Default AddComponent Calls:
	auto daeLogoObject = std::make_unique<GameObject>();
	//daeLogoObject->AddComponent<Transform>(); //Adding a component that exists on the same component will return early + log to console
	daeLogoObject->AddComponent<Texture>()->SetTexture("logo.tga");

	//Getting a Component and modifying its state:
	daeLogoObject->GetComponent<Transform>()->SetLocalPosition(216.0f, 180.0f, 0.0f);

	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	auto titleObject = std::make_unique<GameObject>();
	titleObject->AddComponentLinkable<Text>(font, "Programming 4 Assignment");
	titleObject->GetComponent<Transform>()->SetLocalPosition(80.0f, 20.0f, 0.0f);
#pragma endregion


	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	auto fpsCounterObject = std::make_unique<GameObject>();
	fpsCounterObject
		->AddComponentLinkable<Text>(smallFont, " ")
		->AddComponentLinkable<FrameCounter>();

	auto playerObject = std::make_unique<GameObject>();
	playerObject->AddComponent<Texture>("Player.png");
	playerObject->GetTransform()->SetLocalPosition({ 320,240,0 });
	playerObject->AddComponent<RotationCmp>(1.f,3.f);

	auto bubble1Object = new GameObject(playerObject.get());
	bubble1Object->AddComponent<Texture>("Bubble1.png");
	bubble1Object->GetTransform()->SetLocalPosition({ 50,0,0 });
	bubble1Object->AddComponent<RotationCmp>(120.f,8.f);

	auto bubble2Object = new GameObject(bubble1Object);
	bubble2Object->AddComponent<Texture>("Bubble2.png");
	bubble2Object->GetTransform()->SetLocalPosition({ 120,80,0 });
	bubble2Object->AddComponent<RotationCmp>(60.f, 15.f);

	scene.Add(std::move(backGroundObject));
	scene.Add(std::move(daeLogoObject));
	scene.Add(std::move(titleObject));
	scene.Add(std::move(fpsCounterObject));

	scene.Add(std::move(playerObject));
	
	
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}