#pragma once
#include <BaseComponent.h>
#include <SDL_render.h>
#include "Texture2D.h"
#include <string>
#include <unordered_map>

#include "TextureComponent.h"
#include "Utility.h"

namespace dae
{
	class AnimationComponent final : public BaseComponent
	{
		
		
		struct AnimationData
		{
			AnimationData() = default;
			AnimationData(Rectangle source, int rows, int cols, int totalFrames, float frameTime = 0.2f) :
			sourceSprite{source}, animationRows(rows), animationCols(cols), totalFrames(totalFrames), frameTime(frameTime)
			{}
			AnimationData(const glm::vec2& initialPosition, const glm::vec2&  srcSize, int rows, int cols, int totalFrames, float frameTime = 0.2f) :
				sourceSprite{ {initialPosition.x, initialPosition.y}, srcSize.x, srcSize.y}, animationRows{ rows }, animationCols{ cols }, totalFrames{ totalFrames }, frameTime{ frameTime }
			{}

			//Initialize animation at the correct position and size on the spritesheet
			Rectangle sourceSprite{};

			//How many rows and columns of SpriteFrames does the animation take up
			int animationRows{};
			int animationCols{};

			int totalFrames{};
			int currentFrame{ 0 };
			float frameTime{ 0.2f };
		};

	public:
		AnimationComponent(GameObject* owner);
		virtual ~AnimationComponent() override = default;

		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;


		void AddAnimation(const std::string& name,const AnimationData& animation);
		void RemoveAnimation(const std::string& name);
		void SetCurrentAnimation(const std::string& name);

		void SetDestinationSize(const glm::vec2& size);

		void Update() override;
		void Render() const override;
		//void LateUpdate() override;
		void RenderImGui() override;
	private:
		TextureComponent* m_texture;
		std::unordered_map<std::string, AnimationData> m_animations{};
		std::pair<std::string, AnimationData> m_currentAnimation{};

		glm::vec2 m_destinationSize{};

		double m_frameTimer{};

	};

}
