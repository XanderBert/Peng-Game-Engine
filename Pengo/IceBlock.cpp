﻿#include "IceBlock.h"
#include "BoxCollider.h"
#include "DirectionComponent.h"
#include "MoveComponent.h"
#include "Pengo.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "TriggerComponent.h"
#include <VelocityComponent.h>

IceBlock::IceBlock() : GameObject()
{
	SetTag("IceBlock");

	//Texture Component
	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("Ice_Block.png");

	//Sprite Renderer Component
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


	//Box Collider Component
	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_SpriteSize);


	//velocity Component
	AddComponent<VelocityComponent>()->SetVelocity(100);
	//Direction Component
	AddComponent<DirectionComponent>()->SetDirection({ 0,0 });
	//Move Component
	AddComponent<MoveComponent>()->SetTunnelingMultiplier(1.f);

	//Trigger Component
	const auto triggerComponent = AddComponent<TriggerComponent>();
	//triggerComponent->DebugRender(true);
	triggerComponent->SetColliderSize({ m_SpriteSize.x + 4, m_SpriteSize.y + 4 });
	triggerComponent->SetColliderOffset({ -2,-2 });
	triggerComponent->SetTag("IceBlockTrigger");
}

IceBlock::~IceBlock()
{

};

void IceBlock::Update()
{
	GameObject::Update();
	UpdateSpriteLogic();
}

void IceBlock::OnCollision(GameObject* /*other*/, bool isTrigger, bool isSenderTrigger)
{
	//Stop the block when it collides again an play the animation.
	if (isTrigger) return;
	if (isSenderTrigger) return;
	const auto moveComp = GetComponent<MoveComponent>();
	if (moveComp->CanMove())
	{
		moveComp->SetCanMove(false);

		if (moveComp->GetDistanceMoved() < 5.f)
		{
			GetComponent<SpriteRenderer>()->Play();
		}
		else
		{
			moveComp->ResetMovement();
		}
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
