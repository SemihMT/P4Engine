#pragma once
#include <glm/vec3.hpp>

#include "BaseComponent.h"

	
namespace dae
{
	class Transform;
	class RotationCmp : public BaseComponent
	{
	public:
		RotationCmp(GameObject* owner, float radius, float rotationTime);
		~RotationCmp() override = default;

		RotationCmp(const RotationCmp& other) = delete; //disable copy constructing
		RotationCmp(RotationCmp&& other) = delete; //disable move constructing
		RotationCmp& operator=(const RotationCmp& other) = delete; //disable copy assignment
		RotationCmp& operator=(RotationCmp&& other) = delete; //disable move assignment


		void Update() override;

	private:
		Transform* m_ownerTransform { nullptr };
		Transform* m_parentTransform { nullptr };

		float m_radius;
		float m_rotationTime;
		float m_currentAngle;
	};

}
