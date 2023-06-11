#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Texture2D;
class Font;

class null_ResourceManager
{
public:
	null_ResourceManager() = default;
	virtual ~null_ResourceManager() = default;

	virtual void Init(const std::string& data) = 0;
	virtual std::shared_ptr<Texture2D> LoadTexture(const std::string& file) = 0;
	virtual std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) = 0;
	virtual std::string GetDataPath() const = 0;
};

class ResourceManager final : public null_ResourceManager
{
public:
	ResourceManager() = default;
	virtual ~ResourceManager() override = default;

	virtual void Init(const std::string& data) override;
	virtual std::shared_ptr<Texture2D> LoadTexture(const std::string& file)override;
	virtual std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size)override;
	virtual std::string GetDataPath() const override { return m_dataPath; }
private:
	std::string m_dataPath;
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_loadedTextures;
	std::unordered_map<std::string, std::shared_ptr<Font>> m_LoadedFonts;
};