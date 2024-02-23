#include "Transform.h"

using namespace dae;

Transform::Transform(float x, float y, float z) : m_position({ x,y,z })
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
