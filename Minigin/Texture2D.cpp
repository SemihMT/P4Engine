#include "Texture2D.h"
#include <glm/trigonometric.hpp>

dae::Texture2D::Texture2D(SDL_Texture* texture) : m_texture{ texture }
{
	//Store the width and height of the texture
	SDL_QueryTexture(texture,nullptr,nullptr,&m_width,&m_height);
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	return { m_width,m_height};
}

float dae::Texture2D::GetAngle(bool degrees) const
{
	if (degrees)
		return m_angle;
	return glm::radians(m_angle);
}

void dae::Texture2D::FlipHorizontal()
{
	if ((m_flipState & SDL_FLIP_HORIZONTAL) == 0)
	{
		m_flipState = static_cast<SDL_RendererFlip>(static_cast<int>(m_flipState) | SDL_FLIP_HORIZONTAL);
	}
	else
	{
		m_flipState = static_cast<SDL_RendererFlip>(static_cast<int>(m_flipState) & ~SDL_FLIP_HORIZONTAL);
	}
}

void dae::Texture2D::FlipVertical()
{
	if ((m_flipState & SDL_FLIP_VERTICAL) == 0)
	{
		m_flipState = static_cast<SDL_RendererFlip>(static_cast<int>(m_flipState) | SDL_FLIP_VERTICAL);
	}
	else
	{
		m_flipState = static_cast<SDL_RendererFlip>(static_cast<int>(m_flipState) & ~SDL_FLIP_VERTICAL);
	}
}

void dae::Texture2D::Rotate(float angle, bool degrees)
{
	if (degrees)
		m_angle = angle;
	else
		m_angle = glm::degrees(angle);
}

SDL_RendererFlip dae::Texture2D::GetSDLFlipState() const
{
	return m_flipState;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

