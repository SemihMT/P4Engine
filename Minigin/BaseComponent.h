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

		
		bool IsDead() const;
		bool IsDisabled() const;
		void Kill();
		void Disable();
		void Enable();

	protected:
		GameObject* GetOwner() const;
		BaseComponent(GameObject* owner);
	private:
		//Non-owning! (GameObjects are owned by scenes, preferably only one scene)
		//Allows the component to access its owner's state
		GameObject* m_owner;
		bool m_isDisabled{ false };
		bool m_isDead{ false };
	};
}


