#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TimeManager.h"
#include "Components.h"
using namespace dae;
void load()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Week 02");

	//Linkable AddComponent Calls:
	const auto backGroundObject = 
		std::make_shared<GameObject>()
		->AddComponentLinkable<Transform>(0.0f, 0.0f, 0.0f)
	    ->AddComponentLinkable<Texture>("background.tga");

	//Default AddComponent Calls:
	const auto daeLogoObject = std::make_shared<GameObject>();
	daeLogoObject->AddComponent<Transform>(); //Adding a Transform component without args will default construct the cmp
	daeLogoObject->AddComponent<Texture>()->SetTexture("logo.tga");

	//Getting a Component and modifying its state:
	daeLogoObject->GetComponent<Transform>()->SetPosition(216.0f, 180.0f, 0.0f);

	auto testCmp = std::make_unique<Transform>(daeLogoObject);
	auto testGO = std::make_shared<GameObject>()->AddComponentLinkable(std::move(testCmp));

	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto titleObject = 
		std::make_shared<GameObject>()
		->AddComponentLinkable<Transform>(80.0f,20.0f,0.0f)
		->AddComponentLinkable<Text>(font, "Programming 4 Assignment");


	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	const auto fpsCounterObject =
		std::make_shared<GameObject>()
		->AddComponentLinkable<Transform>(0.0f, 0.0f, 0.0f)
		->AddComponentLinkable<Text>(smallFont, " ")
		->AddComponentLinkable<FrameCounter>();

	scene.Add(backGroundObject);
	scene.Add(daeLogoObject);
	scene.Add(titleObject);
	scene.Add(fpsCounterObject);
	scene.Add(testGO);
	
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}