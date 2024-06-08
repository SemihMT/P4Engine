#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "AnimationComponent.h"
#include "BubbleMovementComponent.h"
#include "ColliderComponent.h"
#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Components.h"
#include "IdleState.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "LevelParser.h"
#include "MoveCommand.h"
#include "PlayerComponent.h"
#include "RigidBodyComponent.h"
#include "ShootBubble.h"
#include "ShootCommand.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "TileComponent.h"
#include "ToggleSoundCommand.h"
#include "ZenChanComponent.h"
using namespace dae;
void load()
{
#pragma region Resources
	const auto font = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 36);
	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);
	const auto smallestFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 12);
#pragma endregion

	auto& scene = SceneManager::GetInstance().CreateScene("Level 1");
	SceneManager::GetInstance().SetCurrentScene("Level 1");

	

	LevelParser parser{ &scene };

	//Registering the color {255,0,0} to create a game object with a TileComponent
	parser.RegisterColor({ 255, 128, 192 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 0 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Wall);
			return tileObject;
		});
	parser.RegisterColor({ 255, 128, 255 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 0 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Platform);
			return tileObject;
		});
	parser.RegisterColor({ 0,128,255 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{
			auto zenChanObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto direction = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			zenChanObject->AddComponent<ZenChanComponent>(direction, ColliderType::Trigger);
			return zenChanObject;
		});
	parser.RegisterColor({ 0,255,0 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{

			auto player = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto startingDirection = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			auto playerNumber = 1;
			player->AddComponent<PlayerComponent>(playerNumber, startingDirection);
			return player;
		});

	parser.RegisterColor({ 255,0,0 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{

			auto player = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto startingDirection = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			auto playerNumber = 2;
			player->AddComponent<PlayerComponent>(playerNumber, startingDirection);
			return player;
		});

	auto scoreUI = std::make_unique<GameObject>(glm::vec3{ 0,0,0 });
	scoreUI->SetName("ScoreObserver");
	scoreUI->AddComponent<Text>(smallFont," ");
	scoreUI->AddComponent<ScoreObserverComponent>();
	scene.Add(std::move(scoreUI));
	

	parser.Parse("Levels/level1Platforms2Players.ppm");

	//Sound Controls
	InputManager::GetInstance().BindKeyboardCommand(SDLK_m, std::make_unique<ToggleSoundCommand>(), KeyState::ButtonUp);

}

int main(int, char* [])
{
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}