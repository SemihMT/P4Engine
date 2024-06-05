#pragma once
#include <BaseComponent.h>

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(GameObject* owner, int playerNumber);
		virtual ~PlayerComponent() override = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:

	};
}
