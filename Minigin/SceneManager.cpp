#include "SceneManager.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	//Rendering all scenes? should probably have one scene selected and render that one
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderImGui()
{
	//Rendering all scenes? should probably have one scene selected and render that one
	for (const auto& scene : m_scenes)
	{
		scene->RenderImGui();
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

	//Update ID
	Scene::m_idCounter++;
	// Only SceneManager can create instances of Scene
	m_scenes.push_back(std::unique_ptr<Scene>(new Scene(name)));
	return *m_scenes.back();
}
