#include "Component.h"
#include "TextureRenderer.h"

#include <iostream>

#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "Texture2D.h"
#include "Transform.h"

TextureRenderer::TextureRenderer(GameObject* owner) : Component(owner)
{
}

TextureRenderer::~TextureRenderer() = default;

void TextureRenderer::Update()
{
}

void TextureRenderer::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
{
}

void TextureRenderer::LateUpdate()
{
}

void TextureRenderer::Render()
{
	if (const auto transformComponent{ GetComponent<Transform>() })
	{
		const auto position{ transformComponent->GetWorldPosition() };

		if (m_usesSrcRect)
		{
			m_pTexture->Render(position, m_SrcRect);
		}
		else
		{
			m_pTexture->Render(position);
		}
	}
}

void TextureRenderer::SetTexture(const std::string& texturePath)
{
	m_pTexture = ServiceLocator::GetInstance().ResourceManager.GetService().LoadTexture(texturePath);
}

glm::vec2 TextureRenderer::GetSize()
{
	return m_pTexture->GetSize();
}

void TextureRenderer::SetSourceRect(const glm::vec2& position, const glm::vec2 size)
{
	m_usesSrcRect = true;

	m_SrcRect.x = static_cast<int>(position.x);
	m_SrcRect.y = static_cast<int>(position.y);
	m_SrcRect.w = static_cast<int>(size.x);
	m_SrcRect.h = static_cast<int>(size.y);
}
