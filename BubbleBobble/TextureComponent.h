#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"
#include <string>
namespace dae
{
	//Static texture
	class TextureComponent final : public BaseComponent
	{
	public: //Construction & RO5
		TextureComponent(GameObject* owner);
		~TextureComponent() override = default;

		explicit TextureComponent(GameObject* owner, const std::string& fileName);

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	public: //Modifier functions

		void SetTexture(const std::string& fileName);
		void FlipHorizontal() const;
		void FlipVertical() const;

		
		bool IsFlippedHorizontal() const;
		bool IsFlippedVertical() const;
		SDL_RendererFlip GetSDLFlipState() const;
		Texture2D* GetTexture2D() const;
		glm::ivec2 GetSize() const;


	private:
		std::shared_ptr<Texture2D> m_texture{};
	};

}
