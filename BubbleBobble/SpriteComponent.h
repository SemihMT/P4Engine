#pragma once
#include <BaseComponent.h>

#include "TextureComponent.h"

namespace dae
{
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(GameObject* owner);
		SpriteComponent(GameObject* owner, const glm::vec2& srcSize, int row, int col, const glm::vec2& destSize);
		

		virtual ~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update() override;
		void Render() const override;
		//void LateUpdate() override;
		//void RenderImgui() override;

		void SetSourceSize(const glm::vec2& newSize);
		void SetSourcePosition(const glm::vec2& newPos);

		void SetDestinationSize(const glm::vec2& newSize);
	private:
		TextureComponent* m_texture{ nullptr };
		Rectangle m_sourceFrame{}; 
		Rectangle m_destinationFrame{};


	};
}
