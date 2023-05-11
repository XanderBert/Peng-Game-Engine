#pragma once
#include "Singleton.h"
#include <string>
#include "Level.h"
#include "rapidxml.hpp"

class LevelLoader
{
public:
	LevelLoader() = default;
	virtual ~LevelLoader() = default;

	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other)noexcept = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other)noexcept = delete;

	virtual void Init(const std::string& levelFolder);
	virtual Level* LoadLevel(const std::string& name) = 0;

protected:
	//Stores the level document in this XML member.
	void OpenFile(const std::string& name);
	rapidxml::xml_document<> m_levelDocument;
private:
	std::string m_LevelFolder;
};

class null_LevelLoader final : public LevelLoader
{
public:
	virtual Level* LoadLevel([[maybe_unused]] const std::string& name) override { return nullptr; }
	virtual void Init([[maybe_unused]] const std::string& levelFolder) override {}
};
