#include "HighScoreDisplayComponent.h"

#include <fstream>
#include <sstream>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Text.h"

dae::HighScoreDisplayComponent::HighScoreDisplayComponent(GameObject* owner) : BaseComponent(owner)
{
	ReadHighScores();
}

void dae::HighScoreDisplayComponent::ReadHighScores()
{
	std::ifstream file(ResourceManager::GetInstance().GetDataPath() + "Highscores.txt");
	if (!file)
	{
		// File does not exist, create it with default text
		std::ofstream outfile(ResourceManager::GetInstance().GetDataPath() + "Highscores.txt");
		outfile << "No highscores yet";
		outfile.close();
		// Re-open the file for reading
		file.open(ResourceManager::GetInstance().GetDataPath() + "Highscores.txt");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string highScores = buffer.str();
	if (highScores.empty())
	{
		highScores = "No highscores yet";
	}

	// Assuming the owner has a method GetComponent to get the TextComponent
	if (auto* textComponent = GetOwner()->GetComponent<Text>())
	{
		textComponent->SetText(highScores);
	}
}
