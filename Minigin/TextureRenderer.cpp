#include "Component.h"
#include "TextureRenderer.h"
#include "Texture2D.h"
#include "Transform.h"

TextureRenderer::TextureRenderer() : Component()
{
}

TextureRenderer::~TextureRenderer() = default;


void TextureRenderer::Update([[maybe_unused]] float deltaT)
{
	//Component::Update(deltaT);
}

void TextureRenderer::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
	//Component::FixedUpdate(fixedTimeStep);
}

void TextureRenderer::LateUpdate([[maybe_unused]] float deltaT)
{
	//Component::LateUpdate(deltaT);
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