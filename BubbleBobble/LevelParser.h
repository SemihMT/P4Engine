#pragma once
#include <functional>
#include <map>
#include <map>
#include <map>
#include <map>
#include <map>
#include <map>
#include <map>
#include <map>
#include <map>
#include <map>
#include <optional>
#include <variant>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "AddScoreCommand.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "Utility.h"

namespace dae
{
	class LevelParser final
	{
		//	The info in the header of the PPM file
		struct PPMInfo
		{
			int width;
			int height;
			int maxColorValue;
		};
	public:
		struct Metadata
		{
			using MetadataValue = std::variant<bool, int, float, glm::vec3 >;
			std::unordered_map<std::string, MetadataValue> metadataMap;

			MetadataValue GetMetadataByType(const std::string& type) { return metadataMap[type]; }
			void StoreMetadata(const std::string& type, const MetadataValue& value) { metadataMap[type] = value; }
		};

	public:
		LevelParser();
		~LevelParser() = default;

		LevelParser(const LevelParser& other) = delete;
		LevelParser(LevelParser&& other) = delete;
		LevelParser& operator=(const LevelParser& other) = delete;
		LevelParser& operator=(LevelParser&& other) = delete;

		void Parse(Scene* scene,const std::string& filename);
		void RegisterColor(const IColor& rgbColor, const std::function<std::unique_ptr<GameObject>(const glm::ivec2& pos, const std::optional<Metadata>& metadata)>& func);
		void AddMetadataHandler(const std::string& newMetadataType, const std::function<void(const std::vector<std::string>&, Metadata&)>& handlerFunction);

	private:

		PPMInfo m_ppmInfo{};
		Scene* m_scene{};


		// This map maps a pixel on the ppm file with a map of strings and values
		// These are metadata values that we can give to pixels, which will help with initializing the level
		// E.g. The direction of a pixel that represents an enemy at (5,2) would be written like:
		// "# Metadata: (5, 2) direction 1 0 0"
		std::map<std::pair<int, int>, Metadata> m_pixelToMetadataMap;

		//List of metadata handler functions
		// Key: type of metadata to handle
		// value: handler function
		using MetadataHandler = std::function<void(const std::vector<std::string>&, Metadata&)>;
		std::unordered_map<std::string, MetadataHandler> m_metadataHandlers
		{
			{"direction",[](const std::vector<std::string>& values, Metadata& data)
			{
				if (values.size() >= 3)
				data.StoreMetadata("direction",glm::vec3{ std::stof(values[0]), std::stof(values[1]), std::stof(values[2]) });
			}},
			{"speed",[](const std::vector<std::string>& values, Metadata& data)
			{
				if (!values.empty())
				data.StoreMetadata("speed",std::stof(values[0]));
			}},
			{"player",[](const std::vector<std::string>& values, Metadata& data)
			{
				if (!values.empty())
				data.StoreMetadata("player",std::stoi(values[0]));
			}}
		};


		//	This map contains a color value R G B [0 - 255]
		//	and a function that returns a unique GameObject ptr
		//	It's up to the user to provide a creation function for a game object for the color they specify
		//	See 'RegisterColor'
		std::map<IColor, std::function<std::unique_ptr<GameObject>(const glm::ivec2& pos, const std::optional<Metadata>& metadata)>> m_colorToObjectMap;



		void ParseMetadata(const std::string& line);
		void ParsePixel(int x, int y, IColor color, const std::optional<Metadata>& metadata);
		void ParsePPM(const std::string& filePath);
		void ParseP3(std::ifstream& file); // Text file
		void ParseP6(std::ifstream& file); // Binary file
		//void ParseText()
	};

	//Registering a color into the parser with a component type
	//This component will get added to a game object that will get moved into the scene

	/*template <typename ComponentType,typename... ComponentArguments>
	void LevelParser::RegisterComponent(const IColor& rgbColor, ComponentArguments&&... args)
	{
		m_colorToComponentMap[rgbColor] = [&](GameObject* owner){owner->AddComponent<ComponentType>(std::forward<ComponentArguments>(args)...);};
	}*/
}
