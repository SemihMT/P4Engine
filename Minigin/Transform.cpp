#include "Transform.h"

using namespace dae;

Transform::Transform(const std::shared_ptr<GameObject>& owner) : BaseComponent(owner)
{
}

Transform::Transform(const std::shared_ptr<GameObject>& owner, float x, float y, float z) : BaseComponent(owner), m_position({ x,y,z })
{

}

const glm::vec3& Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
