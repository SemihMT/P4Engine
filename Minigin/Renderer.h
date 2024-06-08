#pragma once
#include <optional>
#include <SDL.h>
#include <glm/vec2.hpp>

#include "Singleton.h"
namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		friend class Singleton<Renderer>;
		Renderer() = default;

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	public:
		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();


		void RenderTexture(
			const Texture2D& texture,                      // The texture to render on the screen
			const glm::vec2& position,                            // The top-left position in window coordinates of the texture
			const std::optional<glm::vec2>& size = std::nullopt,  // If provided: the texture will be rendered with a custom width and height
			const std::optional<SDL_Rect>& srcRect = std::nullopt // If provided: the part of the texture to render (source rectangle)
		) const;

		////Render a texture2d with the top left position on x,y
		//void RenderTexture(const Texture2D& texture, float x, float y) const;
		////Render a texture2d with the top left position on x,y and a custom size (w & h)
		//void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		////Render a part of a texture2d (src) with a custom position and size on the screen (dst)
		//void RenderTexture(const Texture2D& texture, SDL_Rect src, SDL_Rect dst) const;
		////Render a part of a texture2d (src) with a custom position on the screen, size = src.size
		//void RenderTexture(const Texture2D& texture, SDL_Rect src, float x, float y) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
		glm::ivec2 GetWindowSize()
		{
			glm::ivec2 size{};
			SDL_GetWindowSize(m_window, &size.x, &size.y);
			return size;
		}
	};
}

