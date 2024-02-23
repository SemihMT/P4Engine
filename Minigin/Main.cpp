#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FrameCounter.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextureCmp.h"
#include "Scene.h"
#include "Text.h"
#include "TimeManager.h"
using namespace dae;
void load()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Week 01");

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

	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto titleObject = 
		std::make_shared<GameObject>()
		->AddComponentLinkable<Transform>(80.0f,20.0f,0.0f)
		->AddComponentLinkable<Text>(font, "Programming 4 Assignment");


	//TimeManager::GetInstance().SetFrameTime(160);

	const auto fpsCounterObject =
		std::make_shared<GameObject>()
		->AddComponentLinkable<Transform>(0.0f, 0.0f, 0.0f)
		->AddComponentLinkable<Text>(font," ")
		->AddComponentLinkable<FrameCounter>();


	//auto texture = std::make_unique<Texture>();
	//texture->SetTexture("background.tga");
	//texture->SetOwner(backGroundObject);
	//backGroundObject->AddComponent<Texture>(std::move(texture));

	scene.Add(backGroundObject);
	scene.Add(daeLogoObject);
	scene.Add(titleObject);
	scene.Add(fpsCounterObject);

	
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}