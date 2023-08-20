#include "LevelLoader.h"
#include "EndingScreen.h"
#include "FpsCounter.h"
#include "Ghost.h"
#include "Hud.h"
#include "HudComponent.h"
#include "InputHandler.h"
#include "IntersectionTile.h"
#include "PacDot.h"
#include "PacMan.h"
#include "PacManComponent.h"
#include "PowerUp.h"
#include "PacManEventObserver.h"
#include "rapidxml_print.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "SkipLevelCommand.h"
#include "StartScreen.h"
#include "VelocityComponent.h"
#include "WallManager.h"
#include <fstream>
#include <iostream>


Scene* LevelLoader::LoadLevel(const int levelId, GameMode gameMode)
{
	m_GameMode = gameMode;

	m_Observers.push_back(std::make_unique<PacManEventObserver>());

	return LoadLevel(levelId);


}

Scene* LevelLoader::LoadLevel(const int levelId)
{
	m_LevelId = levelId;

	//Show Ending Screen if needed
	if (levelId == m_AmountOfLevels + 1)
		return LoadEndingScreen();

	//Delete the old scene
	SceneManager::GetInstance().GetActiveScene()->MarkForDeletion();

	//Create the new scene
	const auto level = "level" + std::to_string(levelId);
	auto& level1 = SceneManager::GetInstance().CreateScene(level);




	//Load the level
	LoadLevelData(level1);

	//Load Pacman / Pacman 2 if needed
	if (m_GameMode == GameMode::SinglePlayer) LoadPacMan(level1, 1);
	else LoadPacMan(level1, 2);

	//Don't Load ghosts if in vs mode
	if (m_GameMode != GameMode::Vs)
	{
		LoadGhosts(level1);
	}


	LoadHud(level1);


	//Add the fps counter
	level1.Add(FpsCounter().GetGameObject());

	return &level1;
}

Scene* LevelLoader::LoadNextLevel()
{
	++m_LevelId;
	return LoadLevel(m_LevelId);
}

void LevelLoader::LoadStartScene()
{
	auto& startScreen = SceneManager::GetInstance().CreateScene("Level0");
	startScreen.Add(StartScreen().GetGameObject());

	m_LevelId = 0;
}

Scene* LevelLoader::LoadEndingScreen()
{
	SaveHighScore();

	//Get the scenemanager
	const SceneManager& sceneManager = SceneManager::GetInstance();

	std::string text{};
	for (const auto object : sceneManager.GetActiveScene()->GetObjects())
	{
		if (const auto hud = object->GetComponent<HudComponent>())
		{
			if (hud->IsMultiplayer())
			{
				text += "Player 1: " + std::to_string(hud->GetHighScore()[0]) + "\nPlayer 2: " + std::to_string(hud->GetHighScore()[1]);
				text += "\nHighScore: " + std::to_string(m_AllHighScores[0]);
			}
			else
			{
				text += "Player 1: " + std::to_string(hud->GetHighScore()[0]);
				text += "\nHighScore: " + std::to_string(m_AllHighScores[0]);
			}
		}
	}


	auto& end = SceneManager::GetInstance().CreateScene("EndingScreen");
	const auto endingScreen = EndingScreen().GetGameObject();
	endingScreen->GetComponent<FontRenderer>()->SetText(text);

	end.Add(endingScreen);

	return &end;
}

void LevelLoader::LoadGhosts(Scene& scene)
{
	m_pGhosts.clear();

	for (auto i = 0; i < 4; ++i)
	{
		m_pGhosts.push_back(Ghost().GetGameObject());

		//Set Velocity
		m_pGhosts[i]->GetComponent<VelocityComponent>()->SetVelocity(45.f + static_cast<float>(m_LevelId) * 5.f);
		scene.Add(m_pGhosts[i]);
	}
}

void LevelLoader::LoadHud(Scene& scene)
{
	scene.Add(Hud().GetGameObject());
}

void LevelLoader::LoadPacMan(Scene& scene, int amount)
{



	for (int i = 0; i < amount; ++i)
	{
		const auto pacMan = PacMan();
		pacMan.GetPacMan()->GetComponent<PacManComponent>()->AttachObserver(m_Observers[0].get());

		if (i == 0)
		{
			pacMan.GetPacMan()->GetComponent<InputHandler>()->SetupInput(false);
		}
		else
		{
			pacMan.GetPacMan()->GetComponent<InputHandler>()->SetupInput(true);

		}


		scene.Add(pacMan.GetPacMan());
	}
}

void LevelLoader::SaveHighScore()
{
	//Get Current Scores
	const SceneManager& sceneManager = SceneManager::GetInstance();
	for (const auto object : sceneManager.GetActiveScene()->GetObjects())
	{
		if (const auto hud = object->GetComponent<HudComponent>())
		{
			m_NewHighScores.emplace_back(hud->GetHighScore()[0]);
		}
	}


	// Load existing high scores from the XML file if it exists
	const auto existingHighScores = LoadExistingHighScores();

	// Combine existing high scores and new high scores
	m_AllHighScores.insert(m_AllHighScores.end(), existingHighScores.begin(), existingHighScores.end());
	m_AllHighScores.insert(m_AllHighScores.end(), m_NewHighScores.begin(), m_NewHighScores.end());

	// Sort the combined high scores in descending order
	std::ranges::sort(m_AllHighScores, std::greater<int>());



	// Create an XML document
	rapidxml::xml_document<> doc;

	// Create a declaration (<?xml version="1.0"?>)
	rapidxml::xml_node<>* declaration = doc.allocate_node(rapidxml::node_declaration);
	declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
	//declaration->append_attribute(doc.allocate_attribute("encoding", "utf-8"));

	doc.append_node(declaration);

	// Create a root node
	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "highscores");
	doc.append_node(root);

	// Write each high score as a new node
	for (int score : m_AllHighScores)
	{
		// Convert the score to string
		std::string scoreStr = std::to_string(score);

		// Create a score node
		rapidxml::xml_node<>* scoreNode = doc.allocate_node(rapidxml::node_element, "score", doc.allocate_string(scoreStr.c_str()));
		root->append_node(scoreNode);
	}

	// Save the XML to a file
	std::ofstream outFile("highscores.xml");

	assert(outFile.is_open() && "Error: Unable to open highscores.xml for writing.");
	if (outFile.is_open())
	{
		outFile << doc;
		outFile.close();
	}


	// Free the allocated memory
	doc.clear();
}

std::vector<int> LevelLoader::LoadExistingHighScores()
{
	std::vector<int> existingHighScores{};

	if (std::ifstream inFile("highscores.xml"); inFile.is_open())
	{
		std::vector<char> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		rapidxml::xml_document<> doc;
		doc.parse<0>(&buffer[0]);

		rapidxml::xml_node<>* root = doc.first_node("highscores");
		if (root)
		{

			for (rapidxml::xml_node<>* scoreNode = root->first_node("score"); scoreNode; scoreNode = scoreNode->next_sibling())
			{
				int score = std::stoi(scoreNode->value());
				existingHighScores.push_back(score);
			}
		}

		doc.clear();
	}

	return existingHighScores;
}

void LevelLoader::LoadLevelData(Scene& scene)
{
	// Read the xml file into a vector
	std::ifstream theFile("name.xml");

	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	//Storing a copy, because when the buffer goes out of scope , the data will be deleted
	std::vector<char> m_XmlBuffer = buffer;

	// Parse the buffer using the xml file parsing library into doc 
	rapidxml::xml_document<> m_LevelDocument;
	m_LevelDocument.parse<0>(&m_XmlBuffer[0]);

	// Access the root node
	const rapidxml::xml_node<>* rootNode = m_LevelDocument.first_node("Level");
	assert(rootNode && "Root Node not found");

	LoadWallsFromFile(scene, rootNode);
	LoadIntersectionsFromFile(scene, rootNode);
	LoadPowerPalletsFromFile(scene, rootNode);
	LoadPacDotsFromFile(scene, rootNode);

}

void LevelLoader::LoadWallsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode)
{
	// Access the Walls
	const rapidxml::xml_node<>* WallsNode = rootNode->first_node("Walls");
	assert(WallsNode && "Walls Node not found");

	//Load The walls
	WallManager wallManager{};
	for (const rapidxml::xml_node<>* objectNode = WallsNode->first_node("Wall"); objectNode; objectNode = objectNode->next_sibling("Wall"))
	{
		std::string objectType = objectNode->first_attribute("path")->value();

		wallManager.AddWall(objectType);
	}

	wallManager.AddWallsToScene(scene);
}

void LevelLoader::LoadIntersectionsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode)
{
	// Access the Intersections
	const rapidxml::xml_node<>* IntersectionsNode = rootNode->first_node("Intersections");
	assert(IntersectionsNode && "IntersectionsNode not found");

	//Load The Intersections
	for (const rapidxml::xml_node<>* objectNode = IntersectionsNode->first_node("IntersectionTile"); objectNode; objectNode = objectNode->next_sibling("IntersectionTile"))
	{
		float x = std::stof(objectNode->first_attribute("x")->value());
		float y = std::stof(objectNode->first_attribute("y")->value());

		std::vector<glm::vec2> directions{};

		for (const rapidxml::xml_node<>* directionNode = objectNode->first_node("Direction"); directionNode; directionNode = directionNode->next_sibling("Direction"))
		{
			float xDir = std::stof(directionNode->first_attribute("x")->value());
			float yDir = std::stof(directionNode->first_attribute("y")->value());

			directions.emplace_back(glm::vec2(xDir, yDir));
		}

		scene.Add(IntersectionTile({ x,y }, directions).GetGameObject());
	}
}

void LevelLoader::LoadPowerPalletsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode)
{
	// Access the PowerUps
	const rapidxml::xml_node<>* PowerUpNode = rootNode->first_node("PowerUps");
	assert(PowerUpNode && "PowerUp not found");


	//Load The PowerUps
	for (const rapidxml::xml_node<>* objectNode = PowerUpNode->first_node("PowerUp"); objectNode; objectNode = objectNode->next_sibling("PowerUp"))
	{
		float x = std::stof(objectNode->first_attribute("x")->value());
		float y = std::stof(objectNode->first_attribute("y")->value());

		scene.Add(PowerUp{ "PacBoost.png", {x,y} }.GetGameObject());
	}
}

void LevelLoader::LoadPacDotsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode)
{
	// Access the PacDots
	const rapidxml::xml_node<>* PacDotNode = rootNode->first_node("PacDots");
	assert(PacDotNode && "PowerUp not found");

	//Load The PacDots
	for (const rapidxml::xml_node<>* objectNode = PacDotNode->first_node("PacDot"); objectNode; objectNode = objectNode->next_sibling("PacDot"))
	{
		float x = std::stof(objectNode->first_attribute("x")->value());
		float y = std::stof(objectNode->first_attribute("y")->value());

		scene.Add(PacDot{ x,y }.GetGameObject());
	}
}