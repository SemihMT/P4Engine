#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif


#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Components.h"
#include "GameSettings.h"
#include "InputManager.h"
#include "LevelParser.h"
#include "MaitaComponent.h"

#include "NextLevelCommand.h"
#include "PlayerComponent.h"
#include "SelectorComponent.h"
#include "SpriteComponent.h"

#include "TileComponent.h"
#include "ToggleSoundCommand.h"
#include "ZenChanComponent.h"
using namespace dae;
void load()
{
#pragma region Resources

#pragma endregion


	auto parser = GameSettings::GetInstance().GetParser();

	//Registering the color {255,0,0} to create a game object with a TileComponent
	//Level 1
	parser->RegisterColor({ 255, 128, 192 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 0 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Wall);
			return tileObject;
		});
	parser->RegisterColor({ 255, 128, 255 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 0 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Platform);
			return tileObject;
		});
	//////
	// Level2
	parser->RegisterColor({ 255, 255, 0 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 1 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Wall);
			return tileObject;
		});
	parser->RegisterColor({ 255, 128, 64 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 1 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Platform);
			return tileObject;
		});
	/////////
	// Level3
	parser->RegisterColor({ 185, 7, 70 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 8 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Wall);
			return tileObject;
		});
	parser->RegisterColor({ 105, 15, 150 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& /*metadata*/)
		{
			auto tileObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			int tileIdx{ 8 };
			tileObject->AddComponent<TileComponent>(tileIdx, ColliderType::Platform);
			return tileObject;
		});
	////////

	parser->RegisterColor({ 0,128,255 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{
			auto zenChanObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto direction = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			zenChanObject->AddComponent<ZenChanComponent>(direction, ColliderType::Trigger);
			return zenChanObject;
		});

	parser->RegisterColor({ 192,192,192 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{
			auto maitaObject = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto direction = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			maitaObject->AddComponent<MaitaComponent>(direction, ColliderType::Trigger);
			return maitaObject;
		});
	parser->RegisterColor({ 0,255,0 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{

			auto player = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto startingDirection = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			auto playerNumber = 1;
			player->AddComponent<PlayerComponent>(playerNumber, startingDirection);
			return player;
		});

	parser->RegisterColor({ 255,0,0 }, [](const glm::ivec2& pos, const std::optional<LevelParser::Metadata>& metadata)
		{

			auto player = std::make_unique<GameObject>(glm::vec3{ pos.x,pos.y,0 });
			auto startingDirection = std::get<glm::vec3>(metadata.value().metadataMap.at("direction"));
			auto playerNumber = 2;
			player->AddComponent<PlayerComponent>(playerNumber, startingDirection);
			return player;
		});






	const auto smallFont = ResourceManager::GetInstance().LoadFont(Text::s_defaultFont, 24);

	auto& titleScene = SceneManager::GetInstance().CreateScene("Title");

	auto bg = std::make_unique<GameObject>(0.0f, 0.0f, 0.0f);
	bg->AddComponent<SpriteComponent>("/Sprites/Menu/Background.png", glm::ivec2{ 256,224 }, 0, 0, glm::ivec2{ 512,448 });

	auto title = std::make_unique<GameObject>(100.0f, 50.0f, 0.0f);
	title->AddComponent<Text>(smallFont, "Choose your gamemode!");

	auto option1 = std::make_unique<GameObject>(164.0f, 150.0f, 0.0f);
	option1->AddComponent<Text>(smallFont, "1. Singleplayer");

	auto option2 = std::make_unique<GameObject>(164.0f, 250.0f, 0.0f);
	option2->AddComponent<Text>(smallFont, "2. Co-op");

	auto option3 = std::make_unique<GameObject>(164.0f, 350.0f, 0.0f);
	option3->AddComponent<Text>(smallFont, "3. Versus");

	auto selector = std::make_unique<GameObject>(100.0f, 150.0f, 0.0f);
	selector->AddComponent<SpriteComponent>("/Sprites/Menu/Twinkles.png", glm::ivec2{ 8,8 }, 0, 0, glm::ivec2{ 32,32 });
	selector->AddComponent<SelectorComponent>();



	titleScene.Add(std::move(bg));
	titleScene.Add(std::move(title));
	titleScene.Add(std::move(selector));
	titleScene.Add(std::move(option1));
	titleScene.Add(std::move(option2));
	titleScene.Add(std::move(option3));
	SceneManager::GetInstance().SetCurrentScene("Title");


	ServiceLocator::GetInstance().GetService<ISoundService>("Sound")->PlayMusic("MainTheme.mp3");
	//Sound Controls
	InputManager::GetInstance().BindKeyboardCommand(SDLK_m, std::make_unique<ToggleSoundCommand>(), KeyState::ButtonUp);
	//Skip to next level
	InputManager::GetInstance().BindKeyboardCommand(SDLK_F1, std::make_unique<NextLevelCommand>(), KeyState::ButtonUp);
}

int main(int, char* [])
{
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}