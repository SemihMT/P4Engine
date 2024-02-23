#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform() = default;
		Transform(float x, float y, float z);
		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);

	private:
		glm::vec3 m_position{};
	};
}
