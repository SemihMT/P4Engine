#include "LevelParser.h"
#include "LevelParser.h"

#include <filesystem>
#include <fstream>

#include "ResourceManager.h"
#include "Scene.h"


dae::LevelParser::LevelParser()
{
}

void dae::LevelParser::Parse(Scene* scene, const std::string& filename)
{
	m_scene = scene;
	const auto extension = std::filesystem::path(filename).extension();
	if (extension == ".ppm")
	{
		ParsePPM(filename);
	}
	//else if(extension.compare(""))
}

void dae::LevelParser::RegisterColor(const IColor& rgbColor,
	const std::function<std::unique_ptr<GameObject>(const glm::ivec2& pos, const std::optional<Metadata>& metadata)>& func)
{
	m_colorToObjectMap[rgbColor] = func;
}

void dae::LevelParser::AddMetadataHandler(const std::string& newMetadataType,
	const std::function<void(const std::vector<std::string>&, Metadata&)>& handlerFunction)
{
	m_metadataHandlers[newMetadataType] = handlerFunction;
}

void dae::LevelParser::ParseMetadata(const std::string& line)
{
	std::cout << "encountered metadata line: " << line << "\n";

	// For reference, a metadata line is structured like this: "# Metadata: (x, y) [type of metadata] [optional: values]
	// Examples:
	// # Metadata: (2, 13) direction 1 0 0
	// # Metadata: (21, 12) speed 5
	// # Metadata: (9, 2) 
	// # Metadata: (21, 12) speed 5
	// Find the pixel for which the metadata is written
	 // Find the coordinates and metadata
	size_t start = line.find('(');
	size_t comma = line.find(',', start);
	size_t end = line.find(')', comma);

	if (start != std::string::npos && comma != std::string::npos && end != std::string::npos)
	{
		int xCoord = std::stoi(line.substr(start + 1, comma - start - 1));
		int yCoord = std::stoi(line.substr(comma + 1, end - comma - 1));

		std::cout << "The x coordinate is: " << xCoord << "\n";
		std::cout << "The y coordinate is: " << yCoord << "\n";

		// Find metadata type
		size_t metadataStart = end + 2;  // Skip ") "
		size_t nextSpace = line.find(' ', metadataStart);
		std::string metadataType = line.substr(metadataStart, nextSpace - metadataStart);

		std::cout << "Metadata type: " << metadataType << "\n";

		// Extract metadata values
		std::vector<std::string> metadataValues;
		std::istringstream valueStream(line.substr(nextSpace + 1));
		std::string value;
		while (valueStream >> value)
		{
			metadataValues.push_back(value);
		}

		std::cout << "Metadata values: ";
		for (const auto& val : metadataValues)
		{
			std::cout << val << " ";
		}
		std::cout << "\n";

		// Store metadata in the map
		Metadata data{};
		const auto it = m_metadataHandlers.find(metadataType);
		if (it != m_metadataHandlers.end())
		{
			it->second(metadataValues, data);
			m_pixelToMetadataMap[std::pair<int, int>{xCoord, yCoord}] = data;
		}
		else
		{
			std::cout << "Unknown or unsupported metadata type: [" << metadataType << "]\n";
		}


	}
}

void dae::LevelParser::ParsePixel(int x, int y, IColor color, const std::optional<Metadata>& metadata)
{
	if (m_colorToObjectMap.contains(color))
	{
		auto gameObject = m_colorToObjectMap[color]({ x,y }, metadata);
		m_scene->Add(std::move(gameObject));
	}
}

void dae::LevelParser::ParsePPM(const std::string& filename)
{
	//Open file for reading
	std::ifstream file(ResourceManager::GetInstance().GetDataPath() + filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << "\n";
		return;
	}

	// Read magic number - See PPM file details: https://netpbm.sourceforge.net/doc/ppm.html
	std::string line;
	std::getline(file, line);
	if (line == "P3")
		ParseP3(file);
	else if (line == "P6")
		ParseP6(file);
	else
	{
		std::cerr << "Unsupported PPM format: " << line << "\n";
		return;
	}


}

void dae::LevelParser::ParseP3(std::ifstream& file)
{
	std::string line;
	// Read comments and metadata
	while (std::getline(file, line))
	{
		//Line starts with # -> metadata OR comment
		if (line[0] == '#')
		{
			//If this line contains metadata
			if (line.find("Metadata:") != std::string::npos)
			{
				ParseMetadata(line);
			}
		}
		else
		{
			break;
		}
	}

	//Store the file information
	std::istringstream ss(line);
	ss >> m_ppmInfo.width >> m_ppmInfo.height;
	file >> m_ppmInfo.maxColorValue;

	for (int y{ }; y < m_ppmInfo.height; ++y)
	{
		for (int x{}; x < m_ppmInfo.width; ++x)
		{
			//Read the color value at x,y
			int r;
			int g;
			int b;

			file >> r >> g >> b;
			IColor color{ r,g,b };

			// Find metadata for the current pixel
			auto it = m_pixelToMetadataMap.find({ x, y });
			std::optional<Metadata> data = (it != m_pixelToMetadataMap.end()) ? std::make_optional(it->second) : std::nullopt;

			ParsePixel(x, y+2, color, data);
		}
	}
}

void dae::LevelParser::ParseP6(std::ifstream& file)
{
	std::string line;
	// Read comments and metadata
	while (std::getline(file, line))
	{
		//Line starts with # -> metadata OR comment
		if (line[0] == '#')
		{
			//If this line contains metadata
			if (line.find("Metadata:") != std::string::npos)
			{
				ParseMetadata(line);
			}
		}
		else
		{
			break;
		}
	}

	//Store the file information
	std::istringstream ss(line);
	ss >> m_ppmInfo.width >> m_ppmInfo.height;
	file >> m_ppmInfo.maxColorValue;


	for (int y{}; y < m_ppmInfo.height; ++y)
	{
		for (int x{}; x < m_ppmInfo.width; ++x)
		{
			// Read the color value at x,y
			int r;
			int g;
			int b;

			file >> r >> g >> b;
			IColor color{ r, g, b };

			// Find metadata for the current pixel
			auto it = m_pixelToMetadataMap.find({ x, y });
			std::optional<Metadata> data = (it != m_pixelToMetadataMap.end()) ? std::make_optional(it->second) : std::nullopt;

			// Parse the pixel with an adjusted y-coordinate
			ParsePixel(x, y + 2, color, data);
		}
	}
}
