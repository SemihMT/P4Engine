#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		explicit Transform(GameObject* owner);
		Transform(GameObject* owner ,float x, float y, float z);
		Transform(GameObject* owner ,const glm::vec3& position);

		//pos
		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const;

		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& position);

		void Translate(float x, float y, float z);
		void Translate(const glm::vec3& translation);

		//scale
		const glm::vec3& GetWorldScale();
		const glm::vec3& GetLocalScale() const;

		void SetLocalScale(float x, float y, float z);
		void SetLocalScale(const glm::vec3& scale);

		//rot
		float GetWorldRotation();
		float GetLocalRotation() const;

		void SetLocalRotation(float r);

		//Dirty Flag
		void SetDirtyFlag() { m_isDirty = true; }

	private:

		bool m_isDirty{};
		void UpdateWorldPosition();
		void UpdateWorldScale();
		void UpdateWorldRotation();
		//primary
		glm::vec3 m_worldPosition{};
		glm::vec3 m_worldScale{};
		float m_worldRotation{};

		//local
		glm::vec3 m_localPosition{};
		glm::vec3 m_localScale{};
		float m_localRotation{};

	};
}
