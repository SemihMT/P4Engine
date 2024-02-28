#pragma once
#include <memory>
namespace dae
{
	class GameObject;
	class BaseComponent
	{
		
	public:
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		
		virtual void Update();
		virtual void Render() const;
		virtual void LateUpdate();

		//Could extend the lifetime of the owning game object if the result of this function gets stored somewhere
		std::shared_ptr<GameObject> GetOwner() const;
		bool IsDead() const;
		bool IsDisabled() const;
		void Kill();
		void Disable();
		void Enable();

	protected:
		
		BaseComponent(const std::shared_ptr<GameObject>& owner);
	private:
		//Non-owning reference to shared ptr (GameObjects are owned by scenes, preferably only one scene)
		//Allows the component to access its owner's state
		std::weak_ptr<GameObject> m_owner;
		bool m_isDisabled{ false };
		bool m_isDead{ false };
	};
}


