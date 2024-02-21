#pragma once
#include <memory>
namespace dae
{
	class GameObject;
	class BaseComponent
	{
		
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	public:
		virtual void Update() {};
		virtual void Render() const {};
		virtual void FixedUpdate() {};
		virtual void LateUpdate() {};
	public:

		void SetOwner(std::shared_ptr<GameObject> owner) {
			m_Owner = owner;
		}
		std::shared_ptr<GameObject> GetOwner() const {
			return m_Owner.lock();
		}

	private:
		//Non-owning reference to shared ptr (GameObjects are owned by scenes, preferably only one scene)
		//Allows the component to access its owner's state
		std::weak_ptr<GameObject> m_Owner;
	};
}


