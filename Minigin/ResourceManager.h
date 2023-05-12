#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.h"

class Texture2D;
class Font;
class ResourceManager
{
public:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;

	virtual void Init(const std::string& data);
	virtual std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
	virtual std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
	virtual std::string GetDataPath() const { return m_dataPath; }
private:
	std::string m_dataPath;
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_loadedTextures;
	std::unordered_map<std::string, std::shared_ptr<Font>> m_LoadedFonts;
};

class null_ResourceManager final : public ResourceManager
{
	virtual void Init([[maybe_unused]] const std::string& data) override {}
	virtual std::shared_ptr<Texture2D> LoadTexture([[maybe_unused]] const std::string& file) override { return nullptr; }
	virtual std::shared_ptr<Font> LoadFont([[maybe_unused]] const std::string& file, [[maybe_unused]] unsigned int size) override { return nullptr; }
	virtual std::string GetDataPath() const override { return ""; }
};