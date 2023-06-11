#pragma once
#include <SDL.h>
#include "Singleton.h"

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer
{
	SDL_Renderer* m_renderer{};
	SDL_Window* m_window{};
	SDL_Color m_clearColor{};
public:
	Renderer() = default;
	virtual ~Renderer() = default;


	virtual void Init(SDL_Window* window);
	virtual void Render() const;
	virtual void Destroy();

	virtual void RenderTexture(const Texture2D& texture, float x, float y) const;
	virtual void RenderTexture(const Texture2D& texture, float x, float y, const SDL_Rect& srcRect) const;
	virtual void RenderRect(const SDL_Rect& rect) const;

	virtual SDL_Renderer* GetSDLRenderer() const { return m_renderer; };

	virtual const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	virtual void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
};

class null_Renderer final : public Renderer
{
	virtual void Init(SDL_Window* /*window*/) override {}
	virtual void Render() const override {}
	virtual void Destroy() override {}
	virtual void RenderTexture(const Texture2D& /*texture*/, float /*x*/, float /*y*/) const override {}
	virtual void RenderTexture(const Texture2D& /*texture*/, float /*x*/, float /*y*/, const SDL_Rect& /*srcRect*/) const override {}
	virtual void RenderRect(const SDL_Rect& /*rect*/) const override {}
	SDL_Renderer* GetSDLRenderer() const override { return nullptr; }
	const SDL_Color& GetBackgroundColor() const override { return *new SDL_Color{ 0, 0, 0, 0 }; }
	virtual void SetBackgroundColor(const SDL_Color& /*color*/) override {}
};