#include "TextureCmp.h"

dae::Texture::Texture(GameObject* owner) : BaseComponent(owner)
{
}

dae::Texture::Texture(GameObject* owner, const std::string& fileName): BaseComponent(owner)
{
	SetTexture(fileName);
}

void dae::Texture::Render() const
{
	const auto owner = GetOwner();
	const auto transform = owner->GetComponent<Transform>();
	const auto pos = transform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::Texture::SetTexture(const std::string& fileName)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(fileName);
}
