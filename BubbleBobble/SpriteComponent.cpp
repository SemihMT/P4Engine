#include "SpriteComponent.h"

dae::SpriteComponent::SpriteComponent(GameObject* owner) :
	BaseComponent(owner),
	m_texture{ GetOwner()->GetComponent<TextureComponent>() },
	m_sourceFrame{ .topLeft = {0,0},.width = static_cast<float>(m_texture->GetSize().x), .height = static_cast<float>(m_texture->GetSize().y) },
	m_destinationFrame{ .topLeft = { GetOwner()->GetTransform()->GetWorldPosition()}, .width = m_sourceFrame.width,.height = m_sourceFrame.height }
{
}

dae::SpriteComponent::SpriteComponent(GameObject* owner, const glm::vec2& srcSize, int row, int col, const glm::vec2& destSize) :
	BaseComponent(owner),
	m_texture{ GetOwner()->GetComponent<TextureComponent>() },
	m_sourceFrame{ .topLeft = {srcSize.x * static_cast<float>(col),srcSize.y * static_cast<float>(row)},.width = srcSize.x, .height = srcSize.y },
	m_destinationFrame{ .topLeft = { GetOwner()->GetTransform()->GetWorldPosition()} , .width = destSize.x,.height = destSize.y }
{
}


void dae::SpriteComponent::Update()
{
	const auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	if (m_destinationFrame.topLeft != glm::vec2{ pos })
		m_destinationFrame.topLeft = pos; //converts the vector automatically
}

void dae::SpriteComponent::Render() const
{

	Renderer::GetInstance().RenderTexture(*m_texture->GetTexture2D(), m_sourceFrame, m_destinationFrame);
}

void dae::SpriteComponent::SetSourceSize(const glm::vec2& newSize)
{
	m_sourceFrame.width = newSize.x;
	m_sourceFrame.height = newSize.y;
}

void dae::SpriteComponent::SetSourcePosition(const glm::vec2& newPos)
{
	m_sourceFrame.topLeft = newPos;
}

void dae::SpriteComponent::SetDestinationSize(const glm::vec2& newSize)
{
	m_destinationFrame.width = newSize.x;
	m_destinationFrame.height = newSize.y;
}
