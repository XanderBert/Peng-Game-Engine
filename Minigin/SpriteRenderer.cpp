#include "SpriteRenderer.h"

#include <stdexcept>

#include "TextureRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject* owner)
	: Component(owner)
{
	if (GetComponent<TextureRenderer>() == nullptr)
	{
		throw std::runtime_error(std::string("Your GameObject needs an TextureRenderer Component for the SpriteRenderer To work"));
	}
}

SpriteRenderer::~SpriteRenderer() = default;

void SpriteRenderer::Update()
{

}

void SpriteRenderer::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void SpriteRenderer::LateUpdate()
{

}

void SpriteRenderer::Render()
{
	GetComponent<TextureRenderer>()->Render();
}

void SpriteRenderer::SetTexture(const std::string& texturePath)
{
	GetComponent<TextureRenderer>()->SetTexture(texturePath);
}

void SpriteRenderer::SetSourceRect(const glm::vec2& position, const glm::vec2 size)
{
	m_SpriteSize = size;
	GetComponent<TextureRenderer>()->SetSourceRect(position, m_SpriteSize);
}
