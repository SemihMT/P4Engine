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
	public:
		virtual void Update();
		virtual void Render() const;
		virtual void LateUpdate();

	public:
		//void SetOwner(std::shared_ptr<GameObject> owner);
		std::shared_ptr<GameObject> GetOwner() const;

	protected:
		BaseComponent(const std::shared_ptr<GameObject>& owner);
	private:
		//Non-owning reference to shared ptr (GameObjects are owned by scenes, preferably only one scene)
		//Allows the component to access its owner's state
		std::weak_ptr<GameObject> m_owner;
	};
}


