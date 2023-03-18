#include <SDL.h>
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"


Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

void Texture2D::Render(const glm::vec2& pos) const
{
	Renderer::GetInstance().RenderTexture(*this, pos.x, pos.y);
}

glm::ivec2 Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	//TODO: Set error that texture has not been set!
	return m_texture;
}

Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}