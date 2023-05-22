#include "LevelLoader.h"

#include <fstream>
//does not need to be singleton.


void LevelLoader::Init(const std::string& levelFolder)
{
	m_LevelFolder = levelFolder;
}

std::unique_ptr<Level> LevelLoader::LoadLevel(const std::string& name)
{
	name;
	return nullptr;
}

void LevelLoader::OpenFile(const std::string& name)
{
	std::ifstream theFile{ name };

	std::vector buffer((std::istreambuf_iterator(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	m_levelDocument.parse<0>(&buffer[0]);
}
