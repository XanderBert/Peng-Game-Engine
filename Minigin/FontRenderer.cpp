#include "FontRenderer.h"

#include <iostream>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Color.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"

FontRenderer::FontRenderer(GameObject* owner) : Component(owner)
{
}

FontRenderer::~FontRenderer() = default;

void FontRenderer::Update()
{
	m_needsUpdate = true;

	//needs: font, color, text
	if (m_needsUpdate && m_font)
	{
		//Looks for color component
		//if there is none it will use white
		GetColor();
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_PointerToText->c_str(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void FontRenderer::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void FontRenderer::LateUpdate()
{
}

void FontRenderer::Render()
{
	//needs: texture, transform
	if (m_textTexture)
	{
		if (const auto transformComponent{ GetComponent<Transform>() })
		{
			const auto pos = transformComponent->GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
		else
		{
			//TODO make own error class
			throw std::runtime_error(std::string("FontRenderer::Render() is dependent on a Transform Component"));
		}
	}
}

void FontRenderer::SetText(std::string* text)
{
	m_PointerToText = text;
	if (m_font) m_needsUpdate = true;
}

void FontRenderer::SetFont(const std::string& fontPath, int fontSize)
{
	m_font = { ResourceManager::GetInstance().LoadFont(fontPath, fontSize) };
	m_needsUpdate = true;
}

void FontRenderer::GetColor()
{
	m_color = SDL_Color(255, 255, 255);
	if (const auto component{ GetComponent<Color>() })
	{
		m_color = component->GetColor();
	}
}