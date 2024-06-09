#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Singleton.h"
#include "Scene.h"
namespace dae
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		Scene& CreateScene(const std::string& name);

		Scene* GetCurrentScene() const;
		void SetCurrentScene(const std::string& name);
		void RemoveScene(const std::string& name);

		void Update();
		void Render();
		void RenderImGui();
		void LateUpdate();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::unique_ptr<Scene>> m_scenes;
		Scene* m_currentScene{};
	};
}

#endif // SCENEMANAGER_H