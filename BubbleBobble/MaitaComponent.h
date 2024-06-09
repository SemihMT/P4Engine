#pragma once
#include <BaseComponent.h>
#include <string>

#include "ColliderComponent.h"
#include "Transform.h"

namespace dae
{
	class MaitaComponent final : public BaseComponent
	{
	public:
		MaitaComponent(GameObject* owner, const glm::vec3& direction, ColliderType type);
		virtual ~MaitaComponent() override = default;

		MaitaComponent(const MaitaComponent& other) = delete;
		MaitaComponent(MaitaComponent&& other) = delete;
		MaitaComponent& operator=(const MaitaComponent& other) = delete;
		MaitaComponent& operator=(MaitaComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		Transform* m_transform;
		int m_srcSize{ 16 };
		int m_dstSize{ 32 };
		std::string m_spriteSheetPath{ "Sprites/Characters/Enemy/MaitaSpriteSheet.png" };
	};
}
