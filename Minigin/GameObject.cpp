#include "GameObject.h"
using namespace dae;

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
			component->Update();
	}
	std::erase_if(m_components, [](const auto& component) { return component->IsDead(); });
}

void GameObject::Render() const
{
	for (auto& component : m_components)
	{
		if (!component->IsDisabled())
			component->Render();
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_components)
	{
		if (!component->IsDisabled())
			component->LateUpdate();
	}
}
