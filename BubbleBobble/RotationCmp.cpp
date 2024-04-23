#include "RotationCmp.h"
#include "GameObject.h"
#include "TimeManager.h"
#include <numbers>

#include "imgui.h"

namespace dae {

	RotationCmp::RotationCmp(GameObject* owner, float radius)
		: BaseComponent(owner),
		m_angle(0),
		m_radius(radius)
	{
	}

	void RotationCmp::Update()
	{
		constexpr float two_pi = 2 * static_cast<float>(std::numbers::pi);
		m_angle += static_cast<float>(TimeManager::GetInstance().DeltaTime()) * m_speed;
		if (m_angle > two_pi) m_angle -= two_pi;
		GetOwner()->GetTransform()->SetLocalPosition({ cos(m_angle) * m_radius, sin(m_angle) * m_radius, 0 });
	}
} // namespace dae
