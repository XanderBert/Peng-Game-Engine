#pragma once
#include <string>
#include <unordered_map>

#include "rapidxml.hpp"
#include "Singleton.h"

class LevelLoader final : public Singleton<LevelLoader>
{
public:
	void Init(const std::string& levelFolder);

private:
	friend class Singleton<LevelLoader>;
	LevelLoader() = default;

	std::string m_LevelFolder;
	//std::unordered_map<std::string, std::string> m_loadedLevels;
};

