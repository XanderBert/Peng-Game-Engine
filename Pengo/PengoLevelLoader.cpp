#include "PengoLevelLoader.h"
#include <fstream>
#include "rapidxml.hpp"

#include "ServiceLocator.h"

void PengoLevelLoader::Init(const std::string& levelFolder)
{
	m_LevelFolder = levelFolder;
}

std::unique_ptr<PengoLevel> PengoLevelLoader::LoadLevel(const std::string& name)
{
	OpenFile(m_LevelFolder + name);
	ParseLevel();
	return nullptr;

}

void PengoLevelLoader::OpenFile(const std::string& name)
{
	std::ifstream theFile{ name };

	std::vector buffer((std::istreambuf_iterator(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	m_levelDocument.parse<0>(&buffer[0]);
}