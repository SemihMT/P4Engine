#include "RotationCmp.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "glm/gtc/constants.hpp"

namespace dae {

    RotationCmp::RotationCmp(GameObject* owner, float radius, float rotationTime)
        : BaseComponent(owner),
        m_radius(radius),
        m_rotationTime(rotationTime),
        m_currentAngle(0),
        m_ownerTransform(owner->GetTransform()),
        m_parentTransform(nullptr)
    {
        if (const GameObject* parent = owner->GetParent())
            m_parentTransform = parent->GetTransform();
    }

    void RotationCmp::Update()
    {
        if (!m_ownerTransform) return;

        m_currentAngle += glm::two_pi<float>() * static_cast<float>(TimeManager::GetInstance().DeltaTime()) / m_rotationTime;

       

        const glm::vec3 center = m_parentTransform ? m_parentTransform->GetWorldPosition() : m_ownerTransform->GetWorldPosition();

        const glm::vec3 circlePos{
            center.x + (m_radius * cosf(m_currentAngle)),
            center.y + (m_radius * sinf(m_currentAngle)),
            0
        }; 

        if(m_parentTransform)
            m_ownerTransform->SetLocalPosition(circlePos - center);
        else
            m_ownerTransform->SetLocalPosition(circlePos);

    }

} // namespace dae
