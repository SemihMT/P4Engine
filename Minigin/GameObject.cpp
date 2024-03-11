#include "GameObject.h"

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

void GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	//Check if new parent is valid
	if (parent == this || m_parent == parent || IsChild(parent))
		return;

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
		m_transform->SetDirtyFlag();
	}
	//Remove this GO from parent's list
	if (m_parent)
	{
		//Find this GO in its parent's m_children list
		const auto it = std::ranges::find_if(m_parent->m_children,
			[&](const std::unique_ptr<GameObject>& ptr) {return ptr.get() == this; });

		//If found
		if (it != m_children.end()) 
		{
			//Release the unique pointer from its cleanup/management duties
			//(to prevent the destructor from being called when we remove it from the owning vector)
			it->release();
			//Remove the released unique pointer from the vector
			//Which would be a unique pointer to nullptr 
			m_parent->m_children.erase(it);
		}
	}

	//We can now overwrite who our parent is
	m_parent = parent;

	if(m_parent)
	{
		//Using emplace_back will construct the unique pointer from the raw this pointer we pass in
		m_parent->m_children.emplace_back(this);
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
			if(!m_children.empty())
			{
				for (const auto& child : m_children)
				{
					child->Update();
				}
			}
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
