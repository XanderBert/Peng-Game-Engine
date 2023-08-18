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
	return LoadLevel(levelId);
}

Scene* LevelLoader::LoadLevel(const int levelId)
{
	m_LevelId = levelId;

	//Show Ending Screen if needed
	if (levelId == m_AmountOfLevels + 1) return LoadEndingScreen();

	//Delete the old scene
	SceneManager::GetInstance().GetActiveScene()->MarkForDeletion();

	//Create the new scene
	const auto level = "level" + std::to_string(levelId);
	auto& level1 = SceneManager::GetInstance().CreateScene(level);



	LoadLevelData(&level1);
	//Load the level

	//Load Pacman / Pacman 2 if needed
	if (m_GameMode == GameMode::SinglePlayer) LoadPacMan(level1, 1);
	else LoadPacMan(level1, 2);

	//LoadPacDot(level1);

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
				text += "Player 1: " + std::to_string(hud->GetHighScore()[0]) + " Player 2: " + std::to_string(hud->GetHighScore()[1]);
				text += " HighScore: " + std::to_string(m_AllHighScores[0]);
			}
			else
			{
				text += "Player 1: " + std::to_string(hud->GetHighScore()[0]);
				text += " HighScore: " + std::to_string(m_AllHighScores[0]);
			}
		}
	}


	auto& end = SceneManager::GetInstance().CreateScene("EndingScreen");
	const auto endingScreen = EndingScreen().GetGameObject();
	endingScreen->GetComponent<FontRenderer>()->SetText(text);

	end.Add(endingScreen);

	return &end;
}


void LevelLoader::LoadPowerUps(Scene& scene)
{
	scene.Add(PowerUp("PacBoost.png", { 8,24 }).GetGameObject());
	scene.Add(PowerUp("PacBoost.png", { 8,184 }).GetGameObject());
	scene.Add(PowerUp("PacBoost.png", { 208,24 }).GetGameObject());
	scene.Add(PowerUp("PacBoost.png", { 208,184 }).GetGameObject());
}

void LevelLoader::LoadGhosts(Scene& scene)
{
	m_pGhosts.clear();

	for (auto i = 0; i < 4; ++i)
	{
		m_pGhosts.push_back(Ghost().GetGameObject());

		//Set Velocity
		m_pGhosts[i]->GetComponent<VelocityComponent>()->SetVelocity(40.f + m_LevelId * 5);
		scene.Add(m_pGhosts[i]);
	}
}

void LevelLoader::LoadHud(Scene& scene)
{
	scene.Add(Hud().GetGameObject());
}

void LevelLoader::LoadPacDot(Scene& scene)
{
#ifdef _DEBUG
	//Row_01
	scene.Add(PacDot(11, 11).GetGameObject());
	scene.Add(PacDot(11, 19).GetGameObject());
	scene.Add(PacDot(11, 35).GetGameObject());
	scene.Add(PacDot(11, 43).GetGameObject());
	scene.Add(PacDot(11, 51).GetGameObject());
	scene.Add(PacDot(11, 59).GetGameObject());
	scene.Add(PacDot(11, 67).GetGameObject());
	scene.Add(PacDot(11, 163).GetGameObject());
	scene.Add(PacDot(11, 171).GetGameObject());
	scene.Add(PacDot(11, 179).GetGameObject());
	scene.Add(PacDot(11, 211).GetGameObject());
	scene.Add(PacDot(11, 219).GetGameObject());
	scene.Add(PacDot(11, 227).GetGameObject());
	scene.Add(PacDot(11, 235).GetGameObject());
#else
	//Row_01
	scene.Add(PacDot(11, 11).GetGameObject());
	scene.Add(PacDot(11, 19).GetGameObject());
	scene.Add(PacDot(11, 35).GetGameObject());
	scene.Add(PacDot(11, 43).GetGameObject());
	scene.Add(PacDot(11, 51).GetGameObject());
	scene.Add(PacDot(11, 59).GetGameObject());
	scene.Add(PacDot(11, 67).GetGameObject());
	scene.Add(PacDot(11, 163).GetGameObject());
	scene.Add(PacDot(11, 171).GetGameObject());
	scene.Add(PacDot(11, 179).GetGameObject());
	scene.Add(PacDot(11, 211).GetGameObject());
	scene.Add(PacDot(11, 219).GetGameObject());
	scene.Add(PacDot(11, 227).GetGameObject());
	scene.Add(PacDot(11, 235).GetGameObject());
	//Row_02
	scene.Add(PacDot(19, 11).GetGameObject());
	scene.Add(PacDot(19, 43).GetGameObject());
	scene.Add(PacDot(19, 67).GetGameObject());
	scene.Add(PacDot(19, 163).GetGameObject());
	scene.Add(PacDot(19, 187).GetGameObject());
	scene.Add(PacDot(19, 211).GetGameObject());
	scene.Add(PacDot(19, 235).GetGameObject());
	//Row_03
	scene.Add(PacDot(27, 11).GetGameObject());
	scene.Add(PacDot(27, 43).GetGameObject());
	scene.Add(PacDot(27, 67).GetGameObject());
	scene.Add(PacDot(27, 163).GetGameObject());
	scene.Add(PacDot(27, 187).GetGameObject());
	scene.Add(PacDot(27, 195).GetGameObject());
	scene.Add(PacDot(27, 203).GetGameObject());
	scene.Add(PacDot(27, 211).GetGameObject());
	scene.Add(PacDot(27, 235).GetGameObject());
	//Row_04
	scene.Add(PacDot(35, 11).GetGameObject());
	scene.Add(PacDot(35, 35).GetGameObject());
	scene.Add(PacDot(35, 43).GetGameObject());
	scene.Add(PacDot(35, 67).GetGameObject());
	scene.Add(PacDot(35, 163).GetGameObject());
	scene.Add(PacDot(35, 211).GetGameObject());
	scene.Add(PacDot(35, 235).GetGameObject());
	//Row_05
	scene.Add(PacDot(43, 11).GetGameObject());
	scene.Add(PacDot(43, 35).GetGameObject());
	scene.Add(PacDot(43, 43).GetGameObject());
	scene.Add(PacDot(43, 67).GetGameObject());
	scene.Add(PacDot(43, 163).GetGameObject());
	scene.Add(PacDot(43, 211).GetGameObject());
	scene.Add(PacDot(43, 235).GetGameObject());
	//Row_06
	scene.Add(PacDot(51, 11).GetGameObject());
	scene.Add(PacDot(51, 19).GetGameObject());
	scene.Add(PacDot(51, 27).GetGameObject());
	scene.Add(PacDot(51, 35).GetGameObject());
	scene.Add(PacDot(51, 43).GetGameObject());
	scene.Add(PacDot(51, 51).GetGameObject());
	scene.Add(PacDot(51, 59).GetGameObject());
	scene.Add(PacDot(51, 67).GetGameObject());
	scene.Add(PacDot(51, 75).GetGameObject());
	scene.Add(PacDot(51, 75).GetGameObject());
	scene.Add(PacDot(51, 83).GetGameObject());
	scene.Add(PacDot(51, 91).GetGameObject());
	scene.Add(PacDot(51, 99).GetGameObject());
	scene.Add(PacDot(51, 107).GetGameObject());
	scene.Add(PacDot(51, 115).GetGameObject());
	scene.Add(PacDot(51, 123).GetGameObject());
	scene.Add(PacDot(51, 131).GetGameObject());
	scene.Add(PacDot(51, 139).GetGameObject());
	scene.Add(PacDot(51, 147).GetGameObject());
	scene.Add(PacDot(51, 155).GetGameObject());
	scene.Add(PacDot(51, 163).GetGameObject());
	scene.Add(PacDot(51, 171).GetGameObject());
	scene.Add(PacDot(51, 179).GetGameObject());
	scene.Add(PacDot(51, 187).GetGameObject());
	scene.Add(PacDot(51, 195).GetGameObject());
	scene.Add(PacDot(51, 203).GetGameObject());
	scene.Add(PacDot(51, 211).GetGameObject());
	scene.Add(PacDot(51, 235).GetGameObject());
	//Row_07
	scene.Add(PacDot(59, 11).GetGameObject());
	scene.Add(PacDot(59, 43).GetGameObject());
	scene.Add(PacDot(59, 163).GetGameObject());
	scene.Add(PacDot(59, 187).GetGameObject());
	scene.Add(PacDot(59, 235).GetGameObject());
	//Row_08
	scene.Add(PacDot(67, 11).GetGameObject());
	scene.Add(PacDot(67, 43).GetGameObject());
	scene.Add(PacDot(67, 163).GetGameObject());
	scene.Add(PacDot(67, 187).GetGameObject());
	scene.Add(PacDot(67, 235).GetGameObject());
	//Row_09
	scene.Add(PacDot(75, 11).GetGameObject());
	scene.Add(PacDot(75, 43).GetGameObject());
	scene.Add(PacDot(75, 51).GetGameObject());
	scene.Add(PacDot(75, 59).GetGameObject());
	scene.Add(PacDot(75, 67).GetGameObject());
	scene.Add(PacDot(75, 163).GetGameObject());
	scene.Add(PacDot(75, 187).GetGameObject());
	scene.Add(PacDot(75, 195).GetGameObject());
	scene.Add(PacDot(75, 203).GetGameObject());
	scene.Add(PacDot(75, 211).GetGameObject());
	scene.Add(PacDot(75, 235).GetGameObject());
	//Row_10
	scene.Add(PacDot(83, 11).GetGameObject());
	scene.Add(PacDot(83, 43).GetGameObject());
	scene.Add(PacDot(83, 67).GetGameObject());
	scene.Add(PacDot(83, 163).GetGameObject());
	scene.Add(PacDot(83, 187).GetGameObject());
	scene.Add(PacDot(83, 211).GetGameObject());
	scene.Add(PacDot(83, 235).GetGameObject());
	//Row_11
	scene.Add(PacDot(91, 11).GetGameObject());
	scene.Add(PacDot(91, 43).GetGameObject());
	scene.Add(PacDot(91, 67).GetGameObject());
	scene.Add(PacDot(91, 163).GetGameObject());
	scene.Add(PacDot(91, 187).GetGameObject());
	scene.Add(PacDot(91, 211).GetGameObject());
	scene.Add(PacDot(91, 235).GetGameObject());
	//Row_12
	scene.Add(PacDot(99, 11).GetGameObject());
	scene.Add(PacDot(99, 19).GetGameObject());
	scene.Add(PacDot(99, 27).GetGameObject());
	scene.Add(PacDot(99, 35).GetGameObject());
	scene.Add(PacDot(99, 43).GetGameObject());
	scene.Add(PacDot(99, 67).GetGameObject());
	scene.Add(PacDot(99, 163).GetGameObject());
	scene.Add(PacDot(99, 171).GetGameObject());
	scene.Add(PacDot(99, 179).GetGameObject());
	scene.Add(PacDot(99, 187).GetGameObject());;
	scene.Add(PacDot(99, 211).GetGameObject());
	scene.Add(PacDot(99, 219).GetGameObject());
	scene.Add(PacDot(99, 227).GetGameObject());
	scene.Add(PacDot(99, 235).GetGameObject());
	//Row_13
	scene.Add(PacDot(107, 43).GetGameObject());
	scene.Add(PacDot(107, 235).GetGameObject());
	//Row_14
	scene.Add(PacDot(115, 43).GetGameObject());
	scene.Add(PacDot(115, 235).GetGameObject());
	//Row_15
	scene.Add(PacDot(123, 11).GetGameObject());
	scene.Add(PacDot(123, 19).GetGameObject());
	scene.Add(PacDot(123, 27).GetGameObject());
	scene.Add(PacDot(123, 35).GetGameObject());
	scene.Add(PacDot(123, 43).GetGameObject());
	scene.Add(PacDot(123, 67).GetGameObject());
	scene.Add(PacDot(123, 163).GetGameObject());
	scene.Add(PacDot(123, 171).GetGameObject());
	scene.Add(PacDot(123, 179).GetGameObject());
	scene.Add(PacDot(123, 187).GetGameObject());;
	scene.Add(PacDot(123, 211).GetGameObject());
	scene.Add(PacDot(123, 219).GetGameObject());
	scene.Add(PacDot(123, 227).GetGameObject());
	scene.Add(PacDot(123, 235).GetGameObject());
	//Row_16
	scene.Add(PacDot(131, 11).GetGameObject());
	scene.Add(PacDot(131, 43).GetGameObject());
	scene.Add(PacDot(131, 67).GetGameObject());
	scene.Add(PacDot(131, 163).GetGameObject());
	scene.Add(PacDot(131, 187).GetGameObject());
	scene.Add(PacDot(131, 211).GetGameObject());
	scene.Add(PacDot(131, 235).GetGameObject());
	//Row_17
	scene.Add(PacDot(139, 11).GetGameObject());
	scene.Add(PacDot(139, 43).GetGameObject());
	scene.Add(PacDot(139, 67).GetGameObject());
	scene.Add(PacDot(139, 163).GetGameObject());
	scene.Add(PacDot(139, 187).GetGameObject());
	scene.Add(PacDot(139, 211).GetGameObject());
	scene.Add(PacDot(139, 235).GetGameObject());
	//Row_18
	scene.Add(PacDot(147, 11).GetGameObject());
	scene.Add(PacDot(147, 43).GetGameObject());
	scene.Add(PacDot(147, 51).GetGameObject());
	scene.Add(PacDot(147, 59).GetGameObject());
	scene.Add(PacDot(147, 67).GetGameObject());
	scene.Add(PacDot(147, 163).GetGameObject());
	scene.Add(PacDot(147, 187).GetGameObject());
	scene.Add(PacDot(147, 195).GetGameObject());
	scene.Add(PacDot(147, 203).GetGameObject());
	scene.Add(PacDot(147, 211).GetGameObject());
	scene.Add(PacDot(147, 235).GetGameObject());
	//Row_19
	scene.Add(PacDot(155, 11).GetGameObject());
	scene.Add(PacDot(155, 43).GetGameObject());
	scene.Add(PacDot(155, 163).GetGameObject());
	scene.Add(PacDot(155, 187).GetGameObject());
	scene.Add(PacDot(155, 235).GetGameObject());
	//Row_20
	scene.Add(PacDot(163, 11).GetGameObject());
	scene.Add(PacDot(163, 43).GetGameObject());
	scene.Add(PacDot(163, 163).GetGameObject());
	scene.Add(PacDot(163, 187).GetGameObject());
	scene.Add(PacDot(163, 235).GetGameObject());
	//Row_21
	scene.Add(PacDot(171, 11).GetGameObject());
	scene.Add(PacDot(171, 19).GetGameObject());
	scene.Add(PacDot(171, 27).GetGameObject());
	scene.Add(PacDot(171, 35).GetGameObject());
	scene.Add(PacDot(171, 43).GetGameObject());
	scene.Add(PacDot(171, 51).GetGameObject());
	scene.Add(PacDot(171, 59).GetGameObject());
	scene.Add(PacDot(171, 67).GetGameObject());
	scene.Add(PacDot(171, 75).GetGameObject());
	scene.Add(PacDot(171, 75).GetGameObject());
	scene.Add(PacDot(171, 83).GetGameObject());
	scene.Add(PacDot(171, 91).GetGameObject());
	scene.Add(PacDot(171, 99).GetGameObject());
	scene.Add(PacDot(171, 107).GetGameObject());
	scene.Add(PacDot(171, 115).GetGameObject());
	scene.Add(PacDot(171, 123).GetGameObject());
	scene.Add(PacDot(171, 131).GetGameObject());
	scene.Add(PacDot(171, 139).GetGameObject());
	scene.Add(PacDot(171, 147).GetGameObject());
	scene.Add(PacDot(171, 155).GetGameObject());
	scene.Add(PacDot(171, 163).GetGameObject());
	scene.Add(PacDot(171, 171).GetGameObject());
	scene.Add(PacDot(171, 179).GetGameObject());
	scene.Add(PacDot(171, 187).GetGameObject());
	scene.Add(PacDot(171, 195).GetGameObject());
	scene.Add(PacDot(171, 203).GetGameObject());
	scene.Add(PacDot(171, 211).GetGameObject());
	scene.Add(PacDot(171, 235).GetGameObject());
	//Row_2
	scene.Add(PacDot(179, 11).GetGameObject());
	scene.Add(PacDot(179, 35).GetGameObject());
	scene.Add(PacDot(179, 43).GetGameObject());
	scene.Add(PacDot(179, 67).GetGameObject());
	scene.Add(PacDot(179, 163).GetGameObject());
	scene.Add(PacDot(179, 211).GetGameObject());
	scene.Add(PacDot(179, 235).GetGameObject());
	//Row_23
	scene.Add(PacDot(187, 11).GetGameObject());
	scene.Add(PacDot(187, 35).GetGameObject());
	scene.Add(PacDot(187, 43).GetGameObject());
	scene.Add(PacDot(187, 67).GetGameObject());
	scene.Add(PacDot(187, 163).GetGameObject());
	scene.Add(PacDot(187, 211).GetGameObject());
	scene.Add(PacDot(187, 235).GetGameObject());
	//Row_24
	scene.Add(PacDot(195, 11).GetGameObject());
	scene.Add(PacDot(195, 43).GetGameObject());
	scene.Add(PacDot(195, 67).GetGameObject());
	scene.Add(PacDot(195, 163).GetGameObject());
	scene.Add(PacDot(195, 187).GetGameObject());
	scene.Add(PacDot(195, 195).GetGameObject());
	scene.Add(PacDot(195, 203).GetGameObject());
	scene.Add(PacDot(195, 211).GetGameObject());
	scene.Add(PacDot(195, 235).GetGameObject());
	//Row_25
	scene.Add(PacDot(203, 11).GetGameObject());
	scene.Add(PacDot(203, 43).GetGameObject());
	scene.Add(PacDot(203, 67).GetGameObject());
	scene.Add(PacDot(203, 163).GetGameObject());
	scene.Add(PacDot(203, 187).GetGameObject());
	scene.Add(PacDot(203, 211).GetGameObject());
	scene.Add(PacDot(203, 235).GetGameObject());
	//Row_26
	scene.Add(PacDot(211, 11).GetGameObject());
	scene.Add(PacDot(211, 19).GetGameObject());
	scene.Add(PacDot(211, 35).GetGameObject());
	scene.Add(PacDot(211, 43).GetGameObject());
	scene.Add(PacDot(211, 51).GetGameObject());
	scene.Add(PacDot(211, 59).GetGameObject());
	scene.Add(PacDot(211, 67).GetGameObject());
	scene.Add(PacDot(211, 163).GetGameObject());
	scene.Add(PacDot(211, 171).GetGameObject());
	scene.Add(PacDot(211, 179).GetGameObject());
	scene.Add(PacDot(211, 211).GetGameObject());
	scene.Add(PacDot(211, 219).GetGameObject());
	scene.Add(PacDot(211, 227).GetGameObject());
	scene.Add(PacDot(211, 235).GetGameObject());
#endif // !_Debug



}

void LevelLoader::LoadPacMan(Scene& scene, int amount)
{
	const auto observer = new PacManEventObserver();



	for (int i = 0; i < amount; ++i)
	{
		const auto pacMan = PacMan();
		pacMan.GetPacMan()->GetComponent<PacManComponent>()->AttachObserver(observer);

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
	//Load the potential new high scores
	//Get the scenemanager
	SceneManager& sceneManager = SceneManager::GetInstance();
	for (const auto object : sceneManager.GetActiveScene()->GetObjects())
	{
		if (const auto hud = object->GetComponent<HudComponent>())
		{
			m_NewHighScores.emplace_back(hud->GetHighScore()[0]);
		}
	}


	// Load existing high scores from the XML file if it exists
	std::vector<int> existingHighScores;


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
	if (outFile.is_open())
	{
		outFile << doc;
		outFile.close();
	}
	else
	{
		// Print an error message if the file couldn't be opened
		std::cout << "Error: Unable to open highscores.xml for writing." << std::endl;
	}

	// Free the allocated memory
	doc.clear();

}

void LevelLoader::LoadLevelData(Scene* scene)
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
	if (!rootNode)
	{
		// Handle the case where the root node is not found
		// throw an exception
		return;
	}




	//
	//----------------------
	//----------------------
	//

	// Access the Walls
	const rapidxml::xml_node<>* WallsNode = rootNode->first_node("Walls");
	if (!WallsNode)
	{
		// Handle the case where the root node is not found
		// throw an exception
		assert(false && "Walls not found");
		return;
	}

	//Load The walls
	WallManager wallManager{};
	for (const rapidxml::xml_node<>* objectNode = WallsNode->first_node("Wall"); objectNode; objectNode = objectNode->next_sibling("Wall"))
	{
		std::string objectType = objectNode->first_attribute("path")->value();

		wallManager.AddWall(objectType);
	}

	wallManager.AddWallsToScene(*scene);





	//
	//----------------------
	//----------------------
	//

	// Access the Intersections
	const rapidxml::xml_node<>* IntersectionsNode = rootNode->first_node("Intersections");
	if (!IntersectionsNode)
	{
		// Handle the case where the root node is not found
		// throw an exception

		assert(false && "IntersectionsNode not found");
		return;
	}

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

		scene->Add(IntersectionTile({ x,y }, directions).GetGameObject());
	}









	//
	//----------------------
	//----------------------
	//

	// Access the PowerUps
	const rapidxml::xml_node<>* PowerUpNode = rootNode->first_node("PowerUps");
	if (!PowerUpNode)
	{
		// Handle the case where the root node is not found
		// throw an exception

		assert(false && "PowerUp not found");
		return;
	}

	//Load The PowerUps
	for (const rapidxml::xml_node<>* objectNode = PowerUpNode->first_node("PowerUp"); objectNode; objectNode = objectNode->next_sibling("PowerUp"))
	{
		float x = std::stof(objectNode->first_attribute("x")->value());
		float y = std::stof(objectNode->first_attribute("y")->value());

		scene->Add(PowerUp{ "PacBoost.png", {x,y} }.GetGameObject());
	}












	//
	//----------------------
	//----------------------
	//

	// Access the PacDots
	const rapidxml::xml_node<>* PacDotNode = rootNode->first_node("PacDots");
	if (!PacDotNode)
	{
		// Handle the case where the root node is not found
		// throw an exception

		assert(false && "PowerUp not found");
		return;
	}

	//Load The Intersections
	for (const rapidxml::xml_node<>* objectNode = PacDotNode->first_node("PacDot"); objectNode; objectNode = objectNode->next_sibling("PacDot"))
	{
		float x = std::stof(objectNode->first_attribute("x")->value());
		float y = std::stof(objectNode->first_attribute("y")->value());

		scene->Add(PacDot{ x,y }.GetGameObject());
	}

}
