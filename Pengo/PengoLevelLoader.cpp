#include "PengoLevelLoader.h"
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "ServiceLocator.h"
#include "SnowBee.h"


PengoLevelLoader::PengoLevelLoader()
{
	m_LevelFolder = ServiceLocator::GetInstance().ResourceManager.GetService().GetDataPath() + "Levels/";
}

PengoLevel* PengoLevelLoader::LoadLevel(const std::string& name)
{
	m_pLevel = std::make_unique<PengoLevel>();

	OpenFile(m_LevelFolder + name);
	ParseLevel();

	return m_pLevel.get();
}

GameObject* PengoLevelLoader::CreateObject(const std::string& type, const glm::vec2& location)
{
	GameObject* object = nullptr;

	if (type == "wall")
	{
		object = new Wall();
	}
	else if (type == "iceBlock")
	{
		object = new IceBlock();
	}
	else if (type == "player")
	{
		object = new Pengo();
	}
	else if (type == "snowBee")
	{
		object = new SnowBee();
	}
	else
	{
		//Todo throw error
		return nullptr;
	}

	//Set the location of the object
	object->GetComponent<Transform>()->SetWorldPosition(location);
	return object;
}

void PengoLevelLoader::OpenFile(const std::string& name)
{
	// Read the xml file into a vector
	std::ifstream theFile(name);

	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');


	//Storing a copy, because when the buffer goes out of scope , the data will be deleted
	m_XmlBuffer = buffer;

	// Parse the buffer using the xml file parsing library into doc 
	m_LevelDocument.parse<0>(&m_XmlBuffer[0]);
}

void PengoLevelLoader::ParseLevel() const
{
	// Access the root node
	const rapidxml::xml_node<>* rootNode = m_LevelDocument.first_node("game");
	if (!rootNode)
	{
		// Handle the case where the root node is not found
		// throw an exception
		std::cout << "Root node not found" << std::endl;
		return;
	}

	// Access the objects
	const rapidxml::xml_node<>* objectsNode = rootNode->first_node("objects");
	if (!objectsNode)
	{
		// Handle the case where the root node is not found
		// throw an exception
		std::cout << "Objects node not found" << std::endl;
		return;
	}


	for (const rapidxml::xml_node<>* objectNode = objectsNode->first_node("object"); objectNode; objectNode = objectNode->next_sibling("object"))
	{
		std::string objectType = objectNode->first_attribute("type")->value();

		float x = std::stof(objectNode->first_attribute("x")->value());
		float y = std::stof(objectNode->first_attribute("y")->value());

		// Add the game object to the level class
		m_pLevel->AddGameObject(CreateObject(objectType, glm::vec2(x, y)));
	}
}