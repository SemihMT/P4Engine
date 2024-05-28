#include "SpriteComponent.h"

dae::SpriteComponent::SpriteComponent(GameObject* owner, const std::string& textureFilePath) :
	BaseComponent(owner),
	m_ownerTransform{ GetOwner()->GetTransform() },
	m_texture{ ResourceManager::GetInstance().LoadTexture(textureFilePath) },
	m_sourceFrame{ 0,0, m_texture->GetSize().x, m_texture->GetSize().y },
	m_destinationFrame{
		 static_cast<int>(GetOwner()->GetTransform()->GetWorldPosition().x),
		 static_cast<int>(GetOwner()->GetTransform()->GetWorldPosition().y),
		 m_sourceFrame.w,
		 m_sourceFrame.h
	},
	m_lastPosition{ GetOwner()->GetTransform()->GetWorldPosition() }
{
}

dae::SpriteComponent::SpriteComponent(GameObject* owner, const std::string& textureFilePath, const glm::ivec2& srcSize, int row, int col, const glm::ivec2& destSize) :
	BaseComponent(owner),
	m_ownerTransform{ GetOwner()->GetTransform() },
	m_texture{ ResourceManager::GetInstance().LoadTexture(textureFilePath) },
	m_sourceFrame{ col * srcSize.x,row * srcSize.y, srcSize.x, srcSize.y },
	m_destinationFrame{
		  static_cast<int>(GetOwner()->GetTransform()->GetWorldPosition().x),
		  static_cast<int>(GetOwner()->GetTransform()->GetWorldPosition().y),
		  destSize.x,
		  destSize.y
	},
	m_lastPosition{ GetOwner()->GetTransform()->GetWorldPosition() }

{
}


void dae::SpriteComponent::Update()
{
	// Update destination frame position to match the owner's world position only if it has changed
	const auto currentPosition = m_ownerTransform->GetWorldPosition();
	if (glm::vec2{ currentPosition } != m_lastPosition)
	{
		SetTextureOrientation();
		m_destinationFrame.x = static_cast<int>(currentPosition.x);
		m_destinationFrame.y = static_cast<int>(currentPosition.y);
		m_lastPosition = currentPosition;
	}
}

void dae::SpriteComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(
		*m_texture,
		glm::vec2{ m_destinationFrame.x,m_destinationFrame.y },
		glm::vec2{ m_destinationFrame.w,m_destinationFrame.h },
		m_sourceFrame);
}

void dae::SpriteComponent::SetSourceSize(const glm::ivec2& newSize)
{
	m_sourceFrame.w = newSize.x;
	m_sourceFrame.h = newSize.y;
}

void dae::SpriteComponent::SetSourcePosition(const glm::ivec2& newPos)
{
	m_sourceFrame.x = newPos.x;
	m_sourceFrame.y = newPos.y;
}

void dae::SpriteComponent::SetDestinationSize(const glm::ivec2& newSize)
{
	m_destinationFrame.w = newSize.x;
	m_destinationFrame.h = newSize.y;
}

void dae::SpriteComponent::SetTextureOrientation()
{

	float forwardX = m_ownerTransform->GetForwardDirection().x;
	bool isFlipped = (m_texture->GetSDLFlipState() == SDL_FLIP_HORIZONTAL);
	bool shouldFlip = ((forwardX > 0) && isFlipped) || ((forwardX < 0) && !isFlipped);

	if (shouldFlip) {
		m_texture->FlipHorizontal();
	}
}
