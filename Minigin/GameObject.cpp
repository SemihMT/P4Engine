#include "GameObject.h"
using namespace dae;
void GameObject::FixedUpdate()
{
	for (auto& component : m_components)
	{
		component->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		component->Update();
	}
}

void GameObject::Render() const
{
	for (auto& component : m_components)
	{
		component->Render();
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_components)
	{
		component->LateUpdate();
	}
}
