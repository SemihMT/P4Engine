#include "Transform.h"

#include "GameObject.h"

using namespace dae;

Transform::Transform(GameObject* owner)
	: BaseComponent(owner),
	m_isDirty(true),
	m_worldPosition(),
	m_worldScale(1.f),
	m_worldRotation(),
	m_localPosition(),
	m_localScale(1.f),
	m_localRotation()
{
}

Transform::Transform(GameObject* owner, float x, float y, float z)
	: BaseComponent(owner),
	m_isDirty(true),
	m_worldPosition(),
	m_worldScale(1.f),
	m_worldRotation(),
	m_localPosition({ x,y,z }),
	m_localScale(1.f),
	m_localRotation()
{

}

Transform::Transform(GameObject* owner, const glm::vec3& position)
	: BaseComponent(owner),
	m_isDirty(true),
	m_worldPosition(),
	m_worldScale(1.f),
	m_worldRotation(),
	m_localPosition(position),
	m_localScale(1.f),
	m_localRotation()
{
}

//World space Getters
const glm::vec3& Transform::GetWorldPosition()
{
	if (m_isDirty)
		UpdateWorldPosition();
	return m_worldPosition;
}

float Transform::GetWorldRotation()
{
	if (m_isDirty)
		UpdateWorldRotation();
	return m_worldRotation;
}
const glm::vec3& Transform::GetWorldScale()
{
	if (m_isDirty)
		UpdateWorldScale();
	return m_localScale;
}


//"Cleaning dirty data"
void Transform::UpdateWorldPosition()
{
	if (m_isDirty)
	{
		const auto parent = GetOwner()->GetParent();

		//Root object -> primary = derived
		if (parent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = parent->GetTransform()->GetWorldPosition() + m_localPosition;
	}
	m_isDirty = false;
}

void Transform::UpdateWorldScale()
{
	if (m_isDirty)
	{
		const auto parent = GetOwner()->GetParent();

		//Root object -> primary = derived
		if (parent == nullptr)
			m_worldScale = m_localScale;
		else
			m_worldScale = parent->GetTransform()->GetWorldScale() + m_localScale;
	}
	m_isDirty = false;
}

void Transform::UpdateWorldRotation()
{
	if (m_isDirty)
	{
		const auto parent = GetOwner()->GetParent();

		//Root object -> primary = derived
		if (parent == nullptr)
			m_worldRotation = m_localRotation;
		else
			m_worldRotation = parent->GetTransform()->GetWorldRotation() + m_localRotation;
	}
	m_isDirty = false;
}


// Local space getters
const glm::vec3& Transform::GetLocalPosition() const
{
	return m_localPosition;
}
const glm::vec3& Transform::GetLocalScale() const
{
	return m_localScale;
}
float Transform::GetLocalRotation() const
{
	return m_localRotation;
}


//Local Getters -> primary data -> setting dirty flag when updated
void Transform::SetLocalPosition(float x, float y, float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
	//the data is "dirty" everytime we modify the primary data
	m_isDirty = true;
}
void Transform::SetLocalPosition(const glm::vec3& position)
{
	m_localPosition = position;
	m_isDirty = true;
}

void Transform::Translate(float x, float y, float z)
{
	m_localPosition.x += x;
	m_localPosition.y += y;
	m_localPosition.z += z;
	m_isDirty = true;

}

void Transform::Translate(const glm::vec3& translation)
{
	m_localPosition += translation;
	m_isDirty = true;

}

void Transform::SetLocalScale(float x, float y, float z)
{
	m_localScale.x = x;
	m_localScale.y = y;
	m_localScale.z = z;
	//the data is "dirty" everytime we modify the primary data
	m_isDirty = true;
}
void Transform::SetLocalScale(const glm::vec3& scale)
{
	m_localScale = scale;
	m_isDirty = true;
}
void Transform::SetLocalRotation(float r)
{
	m_localRotation = r;
	m_isDirty = true;

}


