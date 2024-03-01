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

		void Update();
		void Render();
		void LateUpdate();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes;
	};
}

#endif // SCENEMANAGER_H