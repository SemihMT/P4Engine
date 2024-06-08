#pragma once
#include <BaseComponent.h>
#include <string>
#include <vector>

#include "Transform.h"

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(GameObject* owner, int playerNumber, const glm::vec3& direction);
		virtual ~PlayerComponent() override = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;
		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;

		void SetMoveSpeed(float speed) { m_speed = speed; }
		const glm::vec3& GetSpawnPosition() const { return m_spawnPosition; }
		const glm::vec3& GetSpawnDirection() const { return m_spawnDirection; }
		int GetPlayerNumber() const { return m_playerNumber; }

	private:
		Transform* m_transform{ nullptr };
		int m_playerNumber{};
		int m_srcSize{ 16 };
		int m_dstSize{ 32 };
		float m_speed{ 64 };
		float m_jumpForce{ 200 };
		glm::vec3 m_spawnPosition{};
		glm::vec3 m_spawnDirection{};
		std::string m_playerSpriteSheet{};
		std::vector<GameObject*> m_bubbles{ 16 };
		

	};
}
