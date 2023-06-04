#include "FontRenderer.h"

#include <iostream>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Color.h"
#include "ServiceLocator.h"
#include "Texture2D.h"
#include "Transform.h"

FontRenderer::FontRenderer(GameObject* owner) : Component(owner)
{
}

FontRenderer::~FontRenderer() = default;

void FontRenderer::Update()
{
	//needs: font, color, text
	if (m_needsUpdate && m_font)
	{
		//Looks for color component
		//if there is none it will use white
		GetColor();
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(ServiceLocator::GetInstance().Renderer.GetService().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void FontRenderer::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
{
}

void FontRenderer::LateUpdate()
{
}

void FontRenderer::Render()
{
	if (m_textTexture)
	{
		if (const auto transformComponent{ m_pOwner->GetComponent<Transform>() })
		{
			const auto pos = transformComponent->GetWorldPosition();
			ServiceLocator::GetInstance().Renderer.GetService().RenderTexture(*m_textTexture, pos.x + m_Offset.x, pos.y + m_Offset.y);
		}
	}
}

void FontRenderer::SetText(const std::string& text)
{
	m_text = text;
	if (m_font) m_needsUpdate = true;
}

void FontRenderer::SetFont(const std::string& fontPath, int fontSize)
{
	m_font = { ServiceLocator::GetInstance().ResourceManager.GetService().LoadFont(fontPath, fontSize) };
}

void FontRenderer::GetColor()
{
	m_color = SDL_Color(255, 255, 255);
	const auto component{ m_pOwner->GetComponent<Color>() };
	if (component != nullptr)
	{
		m_color = component->GetColor();
	}
}

void FontRenderer::SetOffset(const glm::vec2& offset)
{
	m_Offset = offset;
}

glm::vec2 FontRenderer::GetOffset() const
{
	return m_Offset;
}
