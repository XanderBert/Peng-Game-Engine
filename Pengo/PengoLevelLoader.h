#pragma once
#include <rapidxml.hpp>
#include "PengoLevel.h"
#include "IceBlock.h"
#include "Pengo.h"

class PengoLevelLoader final
{
public:
	PengoLevelLoader();
	~PengoLevelLoader() = default;

	PengoLevelLoader(const PengoLevelLoader& other) = delete;
	PengoLevelLoader(PengoLevelLoader&& other)noexcept = delete;
	PengoLevelLoader& operator=(const PengoLevelLoader& other) = delete;
	PengoLevelLoader& operator=(PengoLevelLoader&& other)noexcept = delete;

	PengoLevel* LoadLevel(const std::string& name);

private:
	//Stores the level document in this XML member.
	void OpenFile(const std::string& name);
	void ParseLevel() const;
	static GameObject* CreateObject(const std::string& type, const glm::vec2& location);
	static GameObject* CreatePlayer(const glm::vec2 location, const std::string& inputType);

	rapidxml::xml_document<> m_LevelDocument;
	std::string m_LevelFolder;
	std::unique_ptr<PengoLevel> m_pLevel;
	std::vector<char> m_XmlBuffer;

};
