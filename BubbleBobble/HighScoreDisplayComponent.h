#pragma once
#include <BaseComponent.h>

namespace dae
{
	class HighScoreDisplayComponent final : public BaseComponent
	{
	public:
		HighScoreDisplayComponent(GameObject* owner);
		virtual ~HighScoreDisplayComponent() override = default;

		HighScoreDisplayComponent(const HighScoreDisplayComponent& other) = delete;
		HighScoreDisplayComponent(HighScoreDisplayComponent&& other) = delete;
		HighScoreDisplayComponent& operator=(const HighScoreDisplayComponent& other) = delete;
		HighScoreDisplayComponent& operator=(HighScoreDisplayComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		void ReadHighScores();
	};
}
