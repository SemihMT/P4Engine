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
		//Removes the gameobject from the scene, allowing something else to store it
		//is useful when re-parenting a gameobject owned by the scene (parent = nullptr) to another gameobject
		//THE RETURNED OBJECT HAS TO GET OWNED BY SOMETHING ELSE TO PREVENT MEMORY LEAKS
		GameObject* Pop(GameObject* object);
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
		bool DisplayGameObject(GameObject* obj, GameObject* draggedObj);
		void DisplayChildren(const GameObject* obj, GameObject* draggedObj);
		void DragGameObject(GameObject* obj);
		void DisplayObjectInfo(const GameObject* obj);
		const GameObject* m_selectedObject{ nullptr };
	};

}
#endif // SCENE_H