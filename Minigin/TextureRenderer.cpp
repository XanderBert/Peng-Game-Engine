#include "Component.h"
#include "TextureRenderer.h"

#include <iostream>

#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"

TextureRenderer::TextureRenderer(GameObject* owner) : Component(owner)
{
}

TextureRenderer::~TextureRenderer() = default;

void TextureRenderer::Update()
{
}

void TextureRenderer::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void TextureRenderer::LateUpdate()
{
}

void TextureRenderer::Render()
{
	if (const auto transformComponent{ GetComponent<Transform>() })
	{
		const auto pos{ transformComponent->GetWorldPosition() };
		m_pTexture->Render(pos);
	}
}

void TextureRenderer::SetTexture(const std::string& texturePath)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

glm::vec2 TextureRenderer::GetSize()
{
	return m_pTexture->GetSize();
}