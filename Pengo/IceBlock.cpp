#include "IceBlock.h"

#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"

IceBlock::IceBlock() : GameObject()
{
	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("Ice_Block.png");

	const auto sprite = AddComponent<SpriteRenderer>();
	sprite->SetSpriteSize(m_SpriteSize);

	for (size_t i{}; i < m_NrFrames; ++i)
	{
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::None);
	}
	sprite->SetMovementDirection(MovementDirection::None);
	sprite->Pause();

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_SpriteSize);
}

IceBlock::~IceBlock()
{
}

void IceBlock::Update()
{
	GameObject::Update();

	if(const auto spriteRenderer = GetComponent<SpriteRenderer>())
	{
		if (spriteRenderer->IsPlaying())
		{
			if (spriteRenderer->GetCurrentSpriteIndexForCurrentDirection() == spriteRenderer->GetLastSpriteIndexForCurrentDirection())
			{
				spriteRenderer->Pause();
				MarkForDeletion();
			}
		}
	}
}

void IceBlock::OnCollision(GameObject* other)
{
	other;
	GetComponent<SpriteRenderer>()->Play();
}
