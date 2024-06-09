#pragma once
#include <BaseComponent.h>
#include <string>

#include "BoulderComponent.h"
#include "ColliderComponent.h"
#include "SceneManager.h"
#include "Transform.h"

namespace dae
{
	class MaitaVersusComponent final : public BaseComponent
	{
	public:
		MaitaVersusComponent(GameObject* owner, const glm::vec3& direction, ColliderType type);
		virtual ~MaitaVersusComponent() override = default;

		MaitaVersusComponent(const MaitaVersusComponent& other) = delete;
		MaitaVersusComponent(MaitaVersusComponent&& other) = delete;
		MaitaVersusComponent& operator=(const MaitaVersusComponent& other) = delete;
		MaitaVersusComponent& operator=(MaitaVersusComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
		void Shoot();
		glm::vec3 GetSpawnPos() const { return m_spawnPos * static_cast<float>(m_srcSize); }
		glm::vec3 GetSpawnDir() const { return m_spawnDir; }
	private:
		Transform* m_transform{};
		int m_dstSize{ 32 };
		int m_srcSize{ 16 };
		float m_speed{ 64.0f };
		std::string m_spritesheetPath{ "/Sprites/Characters/Enemy/MaitaSpriteSheet.png" };
		glm::vec3 m_spawnPos{};
		glm::vec3 m_spawnDir{};

	};
}
