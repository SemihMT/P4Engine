#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
using namespace dae;
void load()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Week 01");
	auto backGroundObject = std::make_shared<GameObject>();
	backGroundObject->AddComponent<Transform>(1.0f, 1.0f, 0.0f);
	backGroundObject->GetComponent<Transform>()->SetOwner(backGroundObject);
	scene.Add(backGroundObject);

	
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}