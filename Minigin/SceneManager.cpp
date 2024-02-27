#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	//Create scene
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	//Update ID
	Scene::m_idCounter++;
	//Store scene in SceneManager
	m_scenes.push_back(scene);
	return *scene;
}
