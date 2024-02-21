#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform() = default;
		Transform(float x, float y, float z) : m_position({ x,y,z }) {};
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z)
		{
			m_position.x = x;
			m_position.y = y;
			m_position.z = z;
		}
	private:
		glm::vec3 m_position{};
	};
}
