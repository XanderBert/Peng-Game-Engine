#pragma once
#include <rapidxml.hpp>
#include "PengoLevel.h"
#include "IceBlock.h"
#include "Pengo.h"
#include "Wall.h"

class PengoLevelLoader final
{
public:
	PengoLevelLoader() = default;
	~PengoLevelLoader() = default;

	PengoLevelLoader(const PengoLevelLoader& other) = delete;
	PengoLevelLoader(PengoLevelLoader&& other)noexcept = delete;
	PengoLevelLoader& operator=(const PengoLevelLoader& other) = delete;
	PengoLevelLoader& operator=(PengoLevelLoader&& other)noexcept = delete;

	virtual void Init(const std::string& levelFolder);
	virtual std::unique_ptr<PengoLevel> LoadLevel(const std::string& name);
private:

	//Stores the level document in this XML member.
	void OpenFile(const std::string& name);
	void ParseLevel();
	rapidxml::xml_document<> m_levelDocument;
	std::string m_LevelFolder;
};
