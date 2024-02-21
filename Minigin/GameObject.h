#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	class GameObject final
	{
		using ComponentPtr = std::unique_ptr<BaseComponent>;
		//Allows the scene to see and call the update and render functions without exposing them to the user
		friend class Scene;

	public:
		//Construction
		explicit GameObject() = default; // No need for any non-default behaviour
		virtual ~GameObject() = default; // ditto.

		GameObject(const GameObject& other) = delete; //disable copy constructing
		GameObject(GameObject&& other) = delete; //disable move constructing
		GameObject& operator=(const GameObject& other) = delete; //disable copy assignment
		GameObject& operator=(GameObject&& other) = delete; //disable move assignment

	private:
		//General Functions
		void FixedUpdate() 
		{
			for (auto& component : m_Components)
			{
				component->FixedUpdate();
			}
		}; 
		void Update() 
		{
			for (auto& component : m_Components)
			{
				component->Update();
			}
		};
		void Render() const 
		{
			for (auto& component : m_Components)
			{
				component->Render();
			}
		};
		void LateUpdate() 
		{
			for (auto& component : m_Components)
			{
				component->LateUpdate();
			}
		};
	public:
		//Helper Functions
		template<typename T>
		T* GetComponent() const
		{
			for (const auto& component : m_Components)
			{
				if (auto castedComponent = dynamic_cast<T*>(component.get()))
				{
					return castedComponent;
				}
			}
			return nullptr;
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must derive from BaseComponent");
			
			// Check if a component of the same type already exists
			for (const auto& component : m_Components)
			{
				if (dynamic_cast<T*>(component.get()) != nullptr)
				{
					//NOTE: Should probably replace std::cout with a logger with overloaded << operator
					std::cout << "Component of the same type already exists!\n";
					
					return nullptr;
				}
			}

			auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
			T* rawPtr = newComponent.get();
			m_Components.push_back(std::move(newComponent));
			return rawPtr;
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Components.erase(
				std::remove_if(m_Components.begin(), m_Components.end(),
					[](const ComponentPtr& component)
					{
						return dynamic_cast<T*>(component.get()) != nullptr;
					}),
				m_Components.end());
		}

	private:

		std::vector<ComponentPtr> m_Components;
	};
}
