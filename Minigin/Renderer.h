#pragma once
#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Singleton.h"

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */

class null_Renderer
{
public:
	null_Renderer() = default;
	virtual ~null_Renderer() = default;

	virtual void Init(SDL_Window* window) = 0;
	virtual void Render() const = 0;
	virtual void Destroy() = 0;
	virtual void RenderTexture(const Texture2D& texture, float x, float y) const = 0;
	virtual void RenderTexture(const Texture2D& texture, float x, float y, const SDL_Rect& srcRect) const = 0;
	virtual void RenderRect(const SDL_Rect& rect) const = 0;
	virtual void RenderRect(const glm::vec2& rect, glm::vec3 color, glm::vec2 size) const = 0;
	virtual SDL_Renderer* GetSDLRenderer() const = 0;
	virtual const SDL_Color& GetBackgroundColor() const = 0;
	virtual void SetBackgroundColor(const SDL_Color& color) = 0;
};

class Renderer final : public null_Renderer
{
	SDL_Renderer* m_renderer{};
	SDL_Window* m_window{};
	SDL_Color m_clearColor{};
public:
	Renderer() = default;
	virtual ~Renderer() override = default;

	virtual void Init(SDL_Window* window) override;
	virtual void Render() const override;
	virtual void Destroy() override;
	virtual void RenderTexture(const Texture2D& texture, float x, float y) const override;
	virtual void RenderTexture(const Texture2D& texture, float x, float y, const SDL_Rect& srcRect) const override;
	virtual void RenderRect(const SDL_Rect& rect) const override;
	virtual void RenderRect(const glm::vec2& rect, glm::vec3 color, glm::vec2 size) const  override;
	virtual SDL_Renderer* GetSDLRenderer() const override { return m_renderer; }
	virtual const SDL_Color& GetBackgroundColor() const  override { return m_clearColor; }
	virtual void SetBackgroundColor(const SDL_Color& color)  override { m_clearColor = color; }
};