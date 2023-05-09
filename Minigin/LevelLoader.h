#pragma once
#include "Singleton.h"
#include <string>
#include "Level.h"
#include "rapidxml.hpp"

class LevelLoader : public Singleton<LevelLoader>
{
public:
	void Init(const std::string& levelFolder);
	virtual Level* LoadLevel(const std::string& name) = 0;

protected:
	//Stores the level document in this XML member.
	void OpenFile(const std::string& name);
	rapidxml::xml_document<> m_levelDocument;


private:
	friend class Singleton<LevelLoader>;
	LevelLoader() = default;
	std::string m_LevelFolder;
}; 