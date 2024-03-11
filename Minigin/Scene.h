#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"
namespace dae
{
	
	class Scene final
	{
		//Friend method for the SceneManager:
		// Allows the SceneManager to call the private ctor
		//friend Scene& SceneManager::CreateScene(const std::string& name);
		friend class SceneManager;
	public:

		void Add(std::unique_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Update();
		void Render() const;
		void RenderImGui();
		void LateUpdate();

		~Scene();
		

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		std::string m_name;
		std::vector< std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;

		void DisplayHierarchy();
		void DisplayGameObject(const GameObject* obj, int i);
	};

}
#endif // SCENE_H