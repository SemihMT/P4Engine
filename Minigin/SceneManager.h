#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Singleton.h"
#include "Scene.h"
namespace dae
{
	//class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetCurrentScene(const std::string& name);
		Scene* GetCurrentScene() const;

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