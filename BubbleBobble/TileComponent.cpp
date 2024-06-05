#include "TileComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"

dae::TileComponent::TileComponent(GameObject* owner, int tileIdx) : BaseComponent(owner), m_transform{ owner->GetTransform() }, m_tileRow{ tileIdx }
{
	owner->SetName("Tile");
	auto pos = m_transform->GetLocalPosition();
	m_transform->SetLocalPosition(pos.x * static_cast<float>(m_tileSize), pos.y * static_cast<float>(m_tileSize), pos.z);

	owner->AddComponent<SpriteComponent>(m_smallTileSheetPath, glm::ivec2{ m_tileSrcSize }, m_tileRow, m_tileCol, glm::ivec2{ m_tileSize });
	owner->AddComponent<ColliderComponent>(m_tileSize, true);

}
