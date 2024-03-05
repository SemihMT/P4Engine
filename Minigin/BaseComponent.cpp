#include "BaseComponent.h"
using namespace dae;

bool BaseComponent::IsDead() const
{
	return m_isDead;
}

bool BaseComponent::IsDisabled() const
{
	return m_isDisabled;
}

void BaseComponent::Disable()
{
	m_isDisabled = true;
}

void BaseComponent::Enable()
{
	m_isDisabled = false;
}


void BaseComponent::Kill()
{
	m_isDead = true;
}

void BaseComponent::Update()
{}

void BaseComponent::Render() const
{}

void BaseComponent::RenderImGui() const
{
}

void BaseComponent::LateUpdate()
{}

//void BaseComponent::SetOwner(std::shared_ptr<GameObject> owner)
//{
//	m_owner = owner;
//}

GameObject* BaseComponent::GetOwner() const
{
	return m_owner;
}

BaseComponent::BaseComponent(GameObject* owner) : m_owner(owner)
{
}
