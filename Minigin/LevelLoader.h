#pragma once
#include <memory>
#include <string>
#include "Level.h"
#include "rapidxml.hpp"

class null_LevelLoader
{
public:
	null_LevelLoader() = default;
	virtual ~null_LevelLoader() = default;

	virtual std::unique_ptr<Level> LoadLevel(const std::string&) = 0;
	virtual void Init(const std::string&) = 0;

protected:
	virtual void OpenFile(const std::string& name) = 0;
};


class LevelLoader : public null_LevelLoader
{
public:
	LevelLoader() = default;
	virtual ~LevelLoader() = default;

	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other)noexcept = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other)noexcept = delete;

	virtual void Init(const std::string& levelFolder) override;
	virtual std::unique_ptr<Level> LoadLevel(const std::string& name) override;

protected:
	//Stores the level document in this XML member.
	void OpenFile(const std::string& name) override;
	rapidxml::xml_document<> m_levelDocument;
private:
	std::string m_LevelFolder;
};