#pragma once
#include <BaseComponent.h>
#include "TextureComponent.h"

namespace dae
{
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(GameObject* owner, const std::string& textureFilePath);
		SpriteComponent(GameObject* owner, const std::string& textureFilePath, const glm::ivec2& srcSize, int row, int col, const glm::ivec2& destSize);

		virtual ~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetSourceSize(const glm::ivec2& newSize);
		void SetSourcePosition(const glm::ivec2& newPos);

		void SetDestinationSize(const glm::ivec2& newSize);
		void SetTextureOrientation();

	private:
		Transform* m_ownerTransform;
		std::shared_ptr<Texture2D> m_texture{ nullptr };
		SDL_Rect m_sourceFrame{};
		SDL_Rect m_destinationFrame{};
		glm::vec2 m_lastPosition{ 0.0f, 0.0f };

	};
}
