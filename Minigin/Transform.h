#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		explicit Transform(const std::shared_ptr<GameObject>& owner);
		Transform(const std::shared_ptr<GameObject>& owner ,float x, float y, float z);
		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);

	private:
		glm::vec3 m_position{};
	};
}
