#include "IceBlock.h"

#include "BoxCollider.h"
#include "IceBlockTrigger.h"
#include "MoveComponent.h"
#include "Pengo.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"

IceBlock::IceBlock()
	: GameObject()
	, m_pTrgger{ new IceBlockTrigger(this) }

{

	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("Ice_Block.png");

	const auto sprite = AddComponent<SpriteRenderer>();
	sprite->SetSpriteSize(m_SpriteSize);



	for (size_t i{}; i < m_NrFrames; ++i)
	{
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::None);
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::Left);
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::Right);
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::Up);
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::Down);
	}


	sprite->Pause();
	sprite->SetFrameTime(0.05f);

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_SpriteSize);


	AddComponent<VelocityComponent>()->SetVelocity(100);
	AddComponent<DirectionComponent>()->SetDirection({ 0,0 });
	AddComponent<MoveComponent>();
}

IceBlock::~IceBlock() = default;

void IceBlock::Update()
{
	GameObject::Update();
	UpdateSpriteLogic();
}

void IceBlock::OnCollision(GameObject* other)
{
	//Stop the block when it collides again an play the animation.
	if (other == m_pTrgger || dynamic_cast<Pengo*>(other) || dynamic_cast<PengoIceBlockTrigger*>(other))
	{
		return;
	}

	if (GetComponent<MoveComponent>()->CanMove())
	{
		GetComponent<SpriteRenderer>()->Play();
		GetComponent<MoveComponent>()->SetCanMove(false);
	}
}


void IceBlock::UpdateSpriteLogic()
{
	//Get SpriteComponent
	if (const auto spriteRenderer = GetComponent<SpriteRenderer>())
	{
		//Check if it is playing
		if (spriteRenderer->IsPlaying())
		{
			//Check if it is at the last frame
			if (spriteRenderer->IsAnimationFinished())
			{
				//Stop playing and mark for deletion
				spriteRenderer->Pause();
				MarkForDeletion();
			}
		}
	}
}
