#include "FontRenderer.h"
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

		const auto textSurface = GetTextSurface();

		if (textSurface == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}


		auto texture = SDL_CreateTextureFromSurface(ServiceLocator::GetInstance().Renderer.GetService().GetSDLRenderer(), textSurface);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}


		SDL_FreeSurface(textSurface);

		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void FontRenderer::FixedUpdate(float /*fixedTimeMStep*/)
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

std::string FontRenderer::GetText() const
{
	return m_text;
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

SDL_Surface* FontRenderer::GetTextSurface() const
{
	//Split up the text in a vector of lines
	std::vector<std::string> lines;
	size_t startPos = 0;
	size_t newlinePos = m_text.find('\n');

	while (newlinePos != std::string::npos)
	{
		lines.push_back(m_text.substr(startPos, newlinePos - startPos));
		startPos = newlinePos + 1;
		newlinePos = m_text.find('\n', startPos);
	}

	lines.push_back(m_text.substr(startPos)); // Add the last line



	//Calculate the height of the text
	const int totalHeight = static_cast<int>(lines.size()) * (TTF_FontHeight(m_font->GetFont()) + m_Padding);


	//Calculate the width of the text
	int desiredWidth = 0;
	for (const std::string& line : lines)
	{
		if (SDL_Surface* lineSurface = TTF_RenderText_Blended(m_font->GetFont(), line.c_str(), m_color))
		{
			desiredWidth = std::max(desiredWidth, lineSurface->w);
			SDL_FreeSurface(lineSurface);
		}
	}


	//Combine every surface into one with lines
	if (SDL_Surface* textSurface = SDL_CreateRGBSurfaceWithFormat(0, desiredWidth, totalHeight, 32, SDL_PIXELFORMAT_RGBA32))
	{
		for (size_t i{}; i < lines.size(); ++i)
		{
			if (SDL_Surface* lineSurface = TTF_RenderText_Blended(m_font->GetFont(), lines[i].c_str(), m_color))
			{
				SDL_Rect targetRect = { 0, static_cast<int>(i * (TTF_FontHeight(m_font->GetFont()) + m_Padding)), lineSurface->w, lineSurface->h };

				SDL_BlitSurface(lineSurface, nullptr, textSurface, &targetRect);

				SDL_FreeSurface(lineSurface);
			}
		}


		return textSurface;
	}


	return nullptr;
}

void FontRenderer::SetPadding(int padding)
{
	m_Padding = padding;
}
