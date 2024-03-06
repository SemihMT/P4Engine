#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class GameObject final
	{
		using ComponentPtr = std::unique_ptr<BaseComponent>;
		//Allows the scene to see and call the update and render functions without exposing them to the user
		friend class Scene;

	public:
#pragma region ctors
		//Construction
		explicit GameObject();
		explicit GameObject(const glm::vec3& position);
		explicit GameObject(float x, float y, float z);
		explicit GameObject(GameObject* parent);
		explicit GameObject(GameObject* parent, const glm::vec3& localPosition);
		explicit GameObject(GameObject* parent, float x, float y, float z);
#pragma endregion
		~GameObject() = default;
	

		GameObject(const GameObject& other) = delete; //disable copy constructing
		GameObject(GameObject&& other) = delete; //disable move constructing
		GameObject& operator=(const GameObject& other) = delete; //disable copy assignment
		GameObject& operator=(GameObject&& other) = delete; //disable move assignment

		//SceneGraph
		GameObject* GetParent(); //returns the pointer -> can be nullptr
		bool IsChild(GameObject* gObject);
		void SetParent(GameObject* parent, bool keepWorldPos);
		size_t GetChildCount() const;
		GameObject* GetChildAt(int idx) const;

		Transform* GetTransform() const { return m_transform; }


#pragma region Enable/Disable GameObject
		bool IsDead() const;
		bool IsDisabled() const;
		void Kill();
		void Disable();
		void Enable();
#pragma endregion

#pragma region Templates
		//Helper Functions
		template<typename T>
		T* GetComponent() const;

		//Adding a Component by unique ptr → The component is created and set-up beforehand
		//Checks if the created comp has the correct owner (this)
		//if not: return nullptr
		template<typename T>
		T* AddComponent(std::unique_ptr<T> component);

		//Adding a Component by Type & arguments → The user can specify a type
		//and (optionally) add parameters if these are known at creation
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);

		//Adding a Component by unique ptr → The component is created and set-up beforehand
		template<typename T>
		GameObject* AddComponentLinkable(std::unique_ptr<T> component);

		//Adding a Component by Type & arguments → The user can specify a type
		//and (optionally) add parameters if these are known at creation
		template<typename T, typename... Args>
		GameObject* AddComponentLinkable(Args&&... args);

		template<typename T>
		void RemoveComponent();
#pragma endregion 
	private:
		//General Functions
		void Update();
		void Render() const;
		void RenderImGui();
		void LateUpdate();

		//SceneGraph
		GameObject* m_parent{nullptr};
		std::vector<std::unique_ptr<GameObject>> m_children{};

		Transform* m_transform{nullptr};
		std::vector<ComponentPtr> m_components{};
		bool m_isDisabled{ false };
		bool m_isDead{ false };
	};



	//=================================
	//
	//  Template Function Definitions
	//
	//=================================
	template <typename T>
	T* GameObject::GetComponent() const
	{
		for (const auto& component : m_components)
		{
			if (auto castedComponent = dynamic_cast<T*>(component.get()))
			{
				return castedComponent;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GameObject::AddComponent(std::unique_ptr<T> component)
	{
		static_assert(std::is_base_of_v<BaseComponent, T>, "T must derive from BaseComponent");

		// Check if a component of the same type already exists
		for (const auto& comp : m_components)
		{
			if (dynamic_cast<T*>(comp.get()) != nullptr)
			{
				std::cout << "Component of the same type already exists!\n";
				return nullptr;
			}
		}

		//Check if the owner of the component we're passing in is this object
		if(component->GetOwner() != this)
		{
			std::cout << "Component "<< typeid(T).name() <<" has the wrong owner!\n";
			return nullptr;;
				
		}

		T* rawPtr = component.get();
		m_components.push_back(std::move(component));
		return rawPtr;
	}

	template <typename T, typename ... Args>
	T* GameObject::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of_v<BaseComponent, T>, "T must derive from BaseComponent");

		// Check if a component of the same type already exists
		for (const auto& component : m_components)
		{
			if (dynamic_cast<T*>(component.get()) != nullptr)
			{
				//NOTE: Should probably replace std::cout with a logger with overloaded << operator
				std::cout << "Component of the same type already exists!\n";

				return nullptr;
			}
		}

		auto newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
		T* rawPtr = newComponent.get();
		m_components.push_back(std::move(newComponent));
		return rawPtr;
	}

	template <typename T>
	GameObject* GameObject::AddComponentLinkable(std::unique_ptr<T> component)
	{
		static_assert(std::is_base_of_v<BaseComponent, T>, "T must derive from BaseComponent");

		// Check if a component of the same type already exists
		for (const auto& comp : m_components)
		{
			if (dynamic_cast<T*>(comp.get()) != nullptr)
			{
				std::cout << "Component of the same type already exists!\n";
				return nullptr;
			}
		}

		//Check if the owner of the component we're passing in is this object
		if (component->GetOwner() != this)
		{
			std::cout << "Component "<< typeid(T).name() << " has the wrong owner!\nSkipped adding to GameObject\n";
			//Return the object without adding the component, 
			return this;

		}

		m_components.push_back(std::move(component));
		return this;
	}

	template <typename T, typename ... Args>
	GameObject* GameObject::AddComponentLinkable(Args&&... args)
	{
		static_assert(std::is_base_of_v<BaseComponent, T>, "T must derive from BaseComponent");

		// Check if a component of the same type already exists
		for (const auto& component : m_components)
		{
			if (dynamic_cast<T*>(component.get()) != nullptr)
			{
				//NOTE: Should probably replace std::cout with a logger with overloaded << operator
				std::cout << "Component of the same type already exists!\n";
				//Will cause the program to crash as the next call to AddCmpLinkable would have to call the function on a nullptr
				return nullptr;
			}
		}
			
		auto newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
		m_components.push_back(std::move(newComponent));
		return this;
	}

	template <typename T>
	void GameObject::RemoveComponent()
	{
		std::erase_if(m_components, [](const ComponentPtr& component)
			{
				return dynamic_cast<T*>(component.get()) != nullptr;
			});
		
	}
}
