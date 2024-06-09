#pragma once
#include <BaseComponent.h>
#include <string>

#include "Transform.h"
#include "Utility.h"
namespace dae
{
	class TileComponent final : public BaseComponent
	{
	public:
		TileComponent(GameObject* owner, int tileIdx, ColliderType type);
		virtual ~TileComponent() override = default;

		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

		//void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
	private:
		Transform* m_transform;
		int m_tileSrcSize{ 8 };
		int m_tileSize{ 16 };
		int m_tileRow{};
		int m_tileCol{ 0 };
		std::string m_smallTileSheetPath{ "Sprites/Levels/Tiles/TileMap.png" };
	};
}
