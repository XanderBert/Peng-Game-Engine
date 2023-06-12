#include <SDL.h>
#include "Texture2D.h"
#include "ServiceLocator.h"


Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

void Texture2D::Render(const glm::vec2& pos) const
{
	ServiceLocator::GetInstance().Renderer.GetService().RenderTexture(*this, pos.x, pos.y);
}

void Texture2D::Render(const glm::vec2& pos, const SDL_Rect& srcRect) const
{
	ServiceLocator::GetInstance().Renderer.GetService().RenderTexture(*this, pos.x, pos.y, srcRect);
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