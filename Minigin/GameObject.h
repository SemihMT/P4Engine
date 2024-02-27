#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	//Enable_shared_from_this allows us to safely create a shared_ptr from the raw 'this' pointer
	//Useful for us, as we're giving the GameObject the responsibility to assign itself as the owner 
	//to any components that get added to it
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
		using ComponentPtr = std::unique_ptr<BaseComponent>;
		//Allows the scene to see and call the update and render functions without exposing them to the user
		friend class Scene;

	public:
		//Construction
		explicit GameObject() = default; // No need for any non-default behaviour
		~GameObject() = default; // ditto.

		GameObject(const GameObject& other) = delete; //disable copy constructing
		GameObject(GameObject&& other) = delete; //disable move constructing
		GameObject& operator=(const GameObject& other) = delete; //disable copy assignment
		GameObject& operator=(GameObject&& other) = delete; //disable move assignment



		//Helper Functions
		template<typename T>
		T* GetComponent() const
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

		//Adding a Component by unique ptr → The component is created and set-up beforehand
		template<typename T>
		T* AddComponent(std::unique_ptr<T> component)
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
			if(component->GetOwner() != shared_from_this())
			{
				std::cout << "Component "<< typeid(T).name() <<" has the wrong owner!\n";
				return nullptr;;
				
			}

			T* rawPtr = component.get();
			m_components.push_back(std::move(component));
			return rawPtr;
		}

		//Adding a Component by Type & arguments → The user can specify a type
		//and (optionally) add 
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
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

			auto newComponent = std::make_unique<T>(shared_from_this(), std::forward<Args>(args)...);
			T* rawPtr = newComponent.get();
			m_components.push_back(std::move(newComponent));
			return rawPtr;
		}

		//Adding a Component by unique ptr → The component is created and set-up beforehand
		template<typename T>
		std::shared_ptr<GameObject> AddComponentLinkable(std::unique_ptr<T> component)
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
			if (component->GetOwner() != shared_from_this())
			{
				std::cout << "Component "<< typeid(T).name() << " has the wrong owner!\nSkipped adding to GameObject\n";
				//Return the object without adding the component, 
				return shared_from_this();

			}

			m_components.push_back(std::move(component));
			return shared_from_this();
		}

		//Adding a Component by Type & arguments → The user can specify a type
		//and (optionally) add 
		template<typename T, typename... Args>
		std::shared_ptr<GameObject> AddComponentLinkable(Args&&... args)
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
			
			auto newComponent = std::make_unique<T>(shared_from_this(), std::forward<Args>(args)...);
			m_components.push_back(std::move(newComponent));
			return shared_from_this();
		}

		template<typename T>
		void RemoveComponent()
		{
			m_components.erase(
				std::remove_if(m_components.begin(), m_components.end(),
					[](const ComponentPtr& component)
					{
						return dynamic_cast<T*>(component.get()) != nullptr;
					}),
				m_components.end());
		}
	private:
		//General Functions

		void Update();

		void Render() const;

		void LateUpdate();



		std::vector<ComponentPtr> m_components;
		bool m_isDead{ false };
	};
}
