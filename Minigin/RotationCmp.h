#pragma once
#include <glm/vec3.hpp>

#include "BaseComponent.h"

	
namespace dae
{
	class Transform;
	class RotationCmp : public BaseComponent
	{
	public:
		RotationCmp(GameObject* owner, float radius);
		~RotationCmp() override = default;

		RotationCmp(const RotationCmp& other) = delete; //disable copy constructing
		RotationCmp(RotationCmp&& other) = delete; //disable move constructing
		RotationCmp& operator=(const RotationCmp& other) = delete; //disable copy assignment
		RotationCmp& operator=(RotationCmp&& other) = delete; //disable move assignment


		void Update() override;
		void RenderImGui() const override;
	private:
		float m_angle;
		float m_speed{ 1 };
		float m_radius;
		
	};

}
