#include "AnimationComponent.h"

#include "GameObject.h"
#include "imgui.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"

dae::AnimationComponent::AnimationComponent(GameObject* owner) :
	BaseComponent(owner),
	m_texture{ GetOwner()->GetComponent<TextureComponent>() }
{
	assert(m_texture != nullptr);
}

void dae::AnimationComponent::AddAnimation(const std::string& name, const AnimationData& animation)
{
	m_animations.insert(std::make_pair(name, animation));
	if (m_animations.size() == 1)
	{
		SetCurrentAnimation(name);
	}
}

void dae::AnimationComponent::RemoveAnimation(const std::string& name)
{
	m_animations.erase(name);
}

void dae::AnimationComponent::SetCurrentAnimation(const std::string& name)
{
	m_currentAnimation = std::make_pair(name, m_animations.at(name));
	m_sourceSprite = m_currentAnimation.second.sourceSprite;
	m_srcSpriteOffset.x = m_currentAnimation.second.sourceSprite.topLeft.x;
	m_srcSpriteOffset.y = m_currentAnimation.second.sourceSprite.topLeft.y;
}

void dae::AnimationComponent::SetDestinationSize(const glm::vec2& size)
{
	m_destinationSize = size;
}


void dae::AnimationComponent::Update()
{
	m_frameTimer += TimeManager::GetInstance().DeltaTime();

	if (m_frameTimer >= m_currentAnimation.second.frameTime)
	{
		m_currentAnimation.second.currentFrame = (m_currentAnimation.second.currentFrame + 1) % m_currentAnimation.second.totalFrames;
		m_sourceSprite.topLeft.x = m_srcSpriteOffset.x + (m_currentAnimation.second.currentFrame % m_currentAnimation.second.animationCols) * m_currentAnimation.second.sourceSprite.width;
		m_sourceSprite.topLeft.y = m_srcSpriteOffset.y + (m_currentAnimation.second.currentFrame / m_currentAnimation.second.animationCols) * m_currentAnimation.second.sourceSprite.height;
		m_frameTimer = 0.0;
	}

}

void dae::AnimationComponent::Render() const
{
	const auto owner = GetOwner();
	const auto transform = owner->GetTransform();
	const auto pos = transform->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_texture->GetTexture2D(), m_sourceSprite, { {pos.x,pos.y},m_destinationSize.x,m_destinationSize.y });
}

void dae::AnimationComponent::RenderImGui()
{
	ImGui::Begin("AnimationComponent");

	ImGui::Text("Current animation: %s\nFrame: %d / %d", m_currentAnimation.first.c_str(), m_currentAnimation.second.currentFrame, m_currentAnimation.second.totalFrames);


	ImGui::End();
}