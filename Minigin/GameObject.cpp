#include "GameObject.h"

#include "SceneManager.h"
#include "Transform.h"
using namespace dae;


GameObject::GameObject()
{
	m_transform = AddComponent<Transform>();
}

GameObject::GameObject(const glm::vec3& position)
{
	m_transform = AddComponent<Transform>(position);
}

GameObject::GameObject(float x, float y, float z)
{
	m_transform = AddComponent<Transform>(x, y, z);
}

GameObject::GameObject(GameObject* parent)
{
	m_transform = AddComponent<Transform>();
	SetParent(parent, true);
}

GameObject::GameObject(GameObject* parent, const glm::vec3& localPosition)
{
	m_transform = AddComponent<Transform>(localPosition);
	SetParent(parent, true);
}

GameObject::GameObject(GameObject* parent, float x, float y, float z)
{
	m_transform = AddComponent<Transform>(x, y, z);
	SetParent(parent, true);
}

void GameObject::SetName(const std::string& name)
{
	if(!name.empty())
	{
		m_name = name;
	}
}

std::string GameObject::GetName() const
{
	return m_name;
}

GameObject* GameObject::GetParent()
{
	return m_parent;
}

bool GameObject::IsChild(GameObject* gObject)
{

	auto it = std::ranges::find_if(m_children,
		[&](const auto& child) {return child.get() == gObject; });

	if (it != m_children.end()) {
		return true; // Value found
	}

	return false; // Value not found


}

bool GameObject::IsParentValid(GameObject* parent)
{
	//Check if new parent is valid
	if (parent == this || m_parent == parent || IsChild(parent))
		return false;
	return true;
}

void GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (!IsParentValid(parent)) return;

	//Set the new transform
	//If we become a root object -> the local position becomes the position we see on screen (world pos)
	//If we become a child of another object we either keep the position on screen, or we force a recalculation our world position based on our new parent
	if (parent == nullptr)
	{
		m_transform->SetLocalPosition(m_transform->GetWorldPosition());
		m_transform->SetLocalScale(m_transform->GetWorldScale());
		m_transform->SetLocalRotation(m_transform->GetWorldRotation());
	}
	else
	{
		if (keepWorldPos)
			m_transform->SetLocalPosition(m_transform->GetWorldPosition() - parent->GetTransform()->GetWorldPosition());
		else
			m_transform->SetLocalPosition({ 0,0,0 });
		m_transform->SetDirtyFlag();
	}


	//If this object already had a parent -> Remove this GO from parent's list
	if (m_parent)
	{
		//Find this GO in its parent's m_children list
		const auto it = std::ranges::find_if(m_parent->m_children,
			[&](const std::unique_ptr<GameObject>& ptr) {return ptr.get() == this; });

		//If found
		if (it != m_parent->m_children.end())
		{
			//Release the unique pointer from its cleanup/management duties
			//(to prevent the destructor from being called when we remove it from the owning vector)
			it->release();
			//Remove the released unique pointer from the vector
			//Which would be a unique pointer to nullptr 
			m_parent->m_children.erase(it);
		}
	}
	//If the parent was nullptr -> the object is owned by the scene, and we want to change it now
	else if (m_parent == nullptr && parent != nullptr)
	{
		//Remove this object from the Scene's GO list
		//Can't use the Remove function as the GO's are stored as unique pointers.
		//Remove would destroy this object
		//The Pop function releases a given object, erases the unique pointer from the scene's list and returns the raw pointer. Ready to transfer ownership
		//Maybe a more descriptive name is necessary...
		 SceneManager::GetInstance().GetCurrentScene()->Pop(this);
		//parent->m_children.emplace_back(obj);

	}
	//We can now overwrite who our parent is
	m_parent = parent;

	if(m_parent)
	{
		//Using emplace_back will construct the unique pointer from the raw this pointer we pass in
		m_parent->m_children.emplace_back(this);
	}
	else
	{
		SceneManager::GetInstance().GetCurrentScene()->Add(std::unique_ptr<GameObject>{this});
	}

}

size_t GameObject::GetChildCount() const
{
	return m_children.size();
}

GameObject* GameObject::GetChildAt(int idx) const
{
	return m_children.at(idx).get();
}

bool GameObject::IsDead() const
{
	return m_isDead;
}

bool GameObject::IsDisabled() const
{
	return m_isDisabled;
}

void GameObject::Disable()
{
	m_isDisabled = true;
}

void GameObject::Enable()
{
	m_isDisabled = false;
}


void GameObject::Kill()
{
	m_isDead = true;
}

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		if (!component->IsDead() && !component->IsDisabled())
		{
			component->Update();
			
		}
	}
	if (!m_children.empty())
	{
		for (const auto& child : m_children)
		{
			child->Update();
		}
	}

	std::erase_if(m_components, [](const auto& component) { return component->IsDead(); });
}

void GameObject::Render() const
{
	for (auto& component : m_components)
	{
		if (!component->IsDisabled())
		{
			component->Render();

		}
	}

	if (!m_children.empty())
	{
		for (const auto& child : m_children)
		{
			child->Render();
		}
	}
}

void GameObject::RenderImGui()
{
	for (auto& component : m_components)
	{
		if (!component->IsDisabled())
		{
			component->RenderImGui();
			
		}
	}
	if (!m_children.empty())
	{
		for (const auto& child : m_children)
		{
			child->RenderImGui();
		}
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_components)
	{
		if (!component->IsDisabled())
		{
			component->LateUpdate();

			if (!m_children.empty())
			{
				for (const auto& child : m_children)
				{
					child->LateUpdate();
				}
			}
		}
	}
}
