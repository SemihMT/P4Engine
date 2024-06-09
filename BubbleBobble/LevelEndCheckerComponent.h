#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelEndCheckerComponent final : public BaseComponent
	{
	public:
		LevelEndCheckerComponent(GameObject* owner);
		virtual ~LevelEndCheckerComponent() override = default;

		LevelEndCheckerComponent(const LevelEndCheckerComponent& other) = delete;
		LevelEndCheckerComponent(LevelEndCheckerComponent&& other) = delete;
		LevelEndCheckerComponent& operator=(const LevelEndCheckerComponent& other) = delete;
		LevelEndCheckerComponent& operator=(LevelEndCheckerComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		void LateUpdate() override;
		//void RenderImgui() override;
	private:

	};
}
