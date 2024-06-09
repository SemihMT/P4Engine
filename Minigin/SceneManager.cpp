#include "SceneManager.h"

void dae::SceneManager::Update()
{
	m_currentScene->Update();
}

void dae::SceneManager::Render()
{
	m_currentScene->Render();
}

void dae::SceneManager::RenderImGui()
{
	m_currentScene->RenderImGui();
}

void dae::SceneManager::LateUpdate()
{
	m_currentScene->LateUpdate();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{

	//Update ID
	Scene::m_idCounter++;
	// Only SceneManager can create instances of Scene
	m_scenes.push_back(std::unique_ptr<Scene>(new Scene(name)));
	return *m_scenes.back();
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	const auto sceneIt = std::ranges::find_if(m_scenes, [&](const auto& scene) { return scene->m_name == name; });

	if (sceneIt != m_scenes.end())
	{
		m_currentScene = sceneIt->get();
	}
}

void dae::SceneManager::RemoveScene(const std::string& name)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{ if ((*it)->GetName() == name)
        {
            // Remove all objects and components from the scene
            (*it)->RemoveAll();

            m_scenes.erase(it);
            if (m_currentScene && m_currentScene->GetName() == name)
            {
                m_currentScene = nullptr;
            }
            return;
		}
	}
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	return m_currentScene;
}
