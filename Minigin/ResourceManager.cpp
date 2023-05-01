#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"

#include <iostream>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file)
{
	//Checks if the texture was already used
	//and if so it will return it from memory
	auto it = m_loadedTextures.find(file);

	if (it != m_loadedTextures.end())
	{
		return std::shared_ptr(it->second);
	}

	//Make a new Texture
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());

	//Did not found texture
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	auto texturePtr = std::make_shared<Texture2D>(texture);
	m_loadedTextures.insert(std::make_pair(file, texturePtr));

	return texturePtr;
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	//Checks if the font was already used
	//and if so it will return it from memory
	auto it = m_LoadedFonts.find(file);

	if (it != m_LoadedFonts.end())
	{
		return std::shared_ptr(it->second);
	}

	auto fontPtr = std::make_shared<Font>(m_dataPath + file, size);

	m_LoadedFonts.insert(std::make_pair(file, fontPtr));
	return fontPtr;
}
