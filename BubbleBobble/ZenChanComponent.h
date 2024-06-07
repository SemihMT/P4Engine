#pragma once
#include <BaseComponent.h>

#include <string>

#include "ColliderComponent.h"
#include "Transform.h"

namespace dae
{
	class ZenChanComponent final : public BaseComponent
	{
	public:
		ZenChanComponent(GameObject* owner, const glm::vec3& direction, ColliderType type);
		virtual ~ZenChanComponent() override = default;

		ZenChanComponent(const ZenChanComponent& other) = delete;
		ZenChanComponent(ZenChanComponent&& other) = delete;
		ZenChanComponent& operator=(const ZenChanComponent& other) = delete;
		ZenChanComponent& operator=(ZenChanComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		Transform* m_transform;
		int m_srcSize{16};
		int m_dstSize{32};
		int m_tileRow{};
		int m_tileCol{0};
		std::string m_spriteSheetPath{"Sprites/Characters/Enemy/ZenChanSpriteSheet.png"};
	};
}