#include "Component.h"
#include "TextureRenderer.h"
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
		const auto& pos{ transformComponent->GetWorldPosition(m_pOwner->GetParent()) };

		m_pTexture->Render(pos);
	}
}

void TextureRenderer::SetTexture(const std::string& texturePath)
{
	//if(ResourceManager::GetInstance().)

	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);

}