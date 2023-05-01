#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Component.h"
#include "SDL.h"

struct SDL_Texture;
/**
 * Simple RAII wrapper for an SDL_Texture
 */
class Texture2D final
{
public:
	SDL_Texture* GetSDLTexture() const;

	explicit Texture2D(SDL_Texture* texture);
	~Texture2D();

	//Called each frame
	void Render(const glm::vec2& pos) const;
	void Render(const glm::vec2& pos, const SDL_Rect& srcRect) const;

	glm::ivec2 GetSize() const;

	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D& operator= (const Texture2D&) = delete;
	Texture2D& operator= (const Texture2D&&) = delete;
private:
	SDL_Texture* m_texture;
};