#pragma once
#include <glm/vec2.hpp>
#include <SDL_render.h>
struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&&) = delete;


		void FlipHorizontal();
		void FlipVertical();
		void Rotate(float angle, bool degrees = true);


		SDL_Texture* GetSDLTexture() const;
		glm::ivec2 GetSize() const;
		SDL_RendererFlip GetSDLFlipState() const;
		float GetAngle(bool degrees = true) const;


	private:
		SDL_Texture* m_texture;
		SDL_RendererFlip m_flipState{ SDL_FLIP_NONE };
		float m_angle{ 0.0f }; //In degrees - See SDL_RenderCopyEx
		int m_width{ 0 };
		int m_height{ 0 };
	};
}
