#pragma once
#include <BaseComponent.h>
#include <string>
#include <unordered_map>
#include "TextureComponent.h"

namespace dae
{

	/* For animations: We assume that each animation is stored in its own row
		 * This way we can define an animation as a row number and a total number of animation frames in the animation
		 * The size
		 */
	struct AnimationData
	{
		AnimationData() = default;
		AnimationData(SDL_Rect source, int numFrames, float frameTime = (1.0f / 60.0f) * 8.0f) :
			sourceSprite{ source }, animationFrames(numFrames), frameTime(frameTime)
		{
		}

		AnimationData(int rowIdx, int numFrames, int srcSize = 16, float frameTime = (1.0f / 60.0f) * 8.0f) :
			sourceSprite{ SDL_Rect{0,rowIdx * srcSize,srcSize,srcSize} }, currentSprite{ sourceSprite }, animationFrames(numFrames), frameTime(frameTime)
		{
		}
		//Initialize animation at the correct position and size on the spritesheet
		SDL_Rect sourceSprite{};
		SDL_Rect currentSprite{};
		//Number of frames in this animation
		int animationFrames{};
		//Time before we skip to the next frame in the animation
		float frameTime{ (1.0f / 60.0f) * 8.0f };

		int currentFrame{ 0 };
	};

	class AnimationComponent final : public BaseComponent
	{
	public:
		AnimationComponent(GameObject* owner, const std::string& textureFilePath);
		virtual ~AnimationComponent() override = default;

		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;


		void AddAnimation(const std::string& name, const AnimationData& animation);
		void RemoveAnimation(const std::string& name);
		void SetCurrentAnimation(const std::string& name);
		const std::string& GetCurrentAnimationName() const { return m_currentAnimation.first; }

		void SetDestinationSize(const glm::vec2& size);

		void Update() override;
		void Render() const override;
		//void LateUpdate() override;
		void RenderImGui() override;
	private:
		Transform* m_ownerTransform;
		std::shared_ptr<Texture2D> m_texture;
		std::unordered_map<std::string, AnimationData> m_animations{};
		std::pair<std::string, AnimationData> m_currentAnimation{};

		SDL_Rect m_sourceSprite{};
		glm::vec2 m_destinationSize{};
		glm::vec2 m_srcSpriteOffset{};

		double m_frameTimer{};

		void SetTextureOrientation();

	};

}
