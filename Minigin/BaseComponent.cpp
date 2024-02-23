#include "BaseComponent.h"
using namespace dae;

void BaseComponent::Update()
{}

void BaseComponent::Render() const
{}

void BaseComponent::FixedUpdate()
{}

void BaseComponent::LateUpdate()
{}

void BaseComponent::SetOwner(std::shared_ptr<GameObject> owner)
{
	m_owner = owner;
}

std::shared_ptr<GameObject> BaseComponent::GetOwner() const
{
	return m_owner.lock();
}
