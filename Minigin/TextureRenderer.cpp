#include "Component.h"
#include "TextureRenderer.h"
#include "Texture2D.h"
#include "Transform.h"

TextureRenderer::TextureRenderer() : Component()
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

void TextureRenderer::Render() const
{
	if (const auto transformComponent{ GetComponent<Transform>() })
	{
		const auto& pos{ transformComponent->GetPosition() };
		m_pTexture->Render(pos);
	}
}

void TextureRenderer::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = std::move(pTexture);
}