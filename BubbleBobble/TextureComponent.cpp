#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject* owner) : BaseComponent(owner)
{
}

dae::TextureComponent::TextureComponent(GameObject* owner, const std::string& fileName): BaseComponent(owner)
{
	SetTexture(fileName);
}

void dae::TextureComponent::SetTexture(const std::string& fileName)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::TextureComponent::FlipHorizontal() const
{
	m_texture->FlipHorizontal();
}

void dae::TextureComponent::FlipVertical() const
{
	m_texture->FlipVertical();
}

bool dae::TextureComponent::IsFlippedHorizontal() const
{
	return (GetSDLFlipState() & SDL_FLIP_HORIZONTAL) != 0;
}

bool dae::TextureComponent::IsFlippedVertical() const
{
	return (GetSDLFlipState() & SDL_FLIP_VERTICAL) != 0;
}

dae::Texture2D* dae::TextureComponent::GetTexture2D() const
{
	return m_texture.get();
}

glm::ivec2 dae::TextureComponent::GetSize() const
{
	return m_texture->GetSize();
}

SDL_RendererFlip dae::TextureComponent::GetSDLFlipState() const
{
	return m_texture->GetSDLFlipState();
}
