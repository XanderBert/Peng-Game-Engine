#include "Wall.h"

#include "TextureRenderer.h"
#include "SpriteRenderer.h"

Wall::Wall() : GameObject()
{
	const auto textureRenderer = AddComponent<TextureRenderer>();
	textureRenderer->SetTexture("Wall_Block.png");
}

Wall::~Wall() = default;