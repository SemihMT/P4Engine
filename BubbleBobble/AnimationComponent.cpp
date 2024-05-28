#include "AnimationComponent.h"

#include "GameObject.h"
#include "imgui.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"

dae::AnimationComponent::AnimationComponent(GameObject* owner, const std::string& textureFilePath) :
	BaseComponent(owner),
	m_ownerTransform(owner->GetTransform())
{
	m_texture = ResourceManager::GetInstance().LoadTexture(textureFilePath);
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
}

void dae::AnimationComponent::SetDestinationSize(const glm::vec2& size)
{
	m_destinationSize = size;
}


void dae::AnimationComponent::Update()
{
	m_frameTimer += TimeManager::GetInstance().DeltaTime();

	SetTextureOrientation();
	auto& [name, animData] = m_currentAnimation;
	if (m_frameTimer >= animData.frameTime)
	{
		animData.currentFrame = (animData.currentFrame + 1) % animData.animationFrames;
		animData.currentSprite.x = animData.sourceSprite.x + animData.currentFrame * animData.sourceSprite.w;
		animData.currentSprite.y = animData.sourceSprite.y;
		m_frameTimer = 0.0;
	}

}

void dae::AnimationComponent::Render() const
{
	const auto pos = m_ownerTransform->GetWorldPosition();
	auto [name, animData] = m_currentAnimation;

	Renderer::GetInstance().RenderTexture(*m_texture, glm::vec2{ pos }, m_destinationSize, animData.currentSprite);
}

void dae::AnimationComponent::RenderImGui()
{
	auto [name, animData] = m_currentAnimation;
	ImGui::Begin("AnimationComponent");

	ImGui::Text("Current animation: %s\nFrame: %d / %d", name.c_str(), animData.currentFrame, animData.animationFrames);


	ImGui::End();
}

void dae::AnimationComponent::SetTextureOrientation()
{

	float forwardX = m_ownerTransform->GetForwardDirection().x;
	bool isFlipped = (m_texture->GetSDLFlipState() == SDL_FLIP_HORIZONTAL);
	bool shouldFlip = ((forwardX > 0) && isFlipped) || ((forwardX < 0) && !isFlipped);

	if (shouldFlip) {
		m_texture->FlipHorizontal();
	}
}
