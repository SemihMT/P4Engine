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

	//Linkable AddComponent Calls:
	auto backGroundObject = std::make_unique<GameObject>();
	backGroundObject->AddComponentLinkable<Texture>("background.tga");

	//Default AddComponent Calls:
	auto daeLogoObject = std::make_unique<GameObject>();
	daeLogoObject->AddComponent<Transform>(); //Adding a Transform component without args will default construct the cmp
	daeLogoObject->AddComponent<Texture>()->SetTexture("logo.tga");

	//Getting a Component and modifying its state:
	daeLogoObject->GetComponent<Transform>()->SetPosition(216.0f, 180.0f, 0.0f);

	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	auto titleObject = std::make_unique<GameObject>();
	titleObject->AddComponentLinkable<Text>(font, "Programming 4 Assignment");
	titleObject->GetComponent<Transform>()->SetPosition(80.0f, 20.0f, 0.0f);


	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	auto fpsCounterObject = std::make_unique<GameObject>();
	fpsCounterObject
		->AddComponentLinkable<Text>(smallFont, " ")
		->AddComponentLinkable<FrameCounter>();

	scene.Add(std::move(backGroundObject));
	scene.Add(std::move(daeLogoObject));
	scene.Add(std::move(titleObject));
	scene.Add(std::move(fpsCounterObject));
	
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}