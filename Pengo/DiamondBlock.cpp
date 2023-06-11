#include "DiamondBlock.h"			 
#include  "BoxCollider.h"
#include "DirectionComponent.h"
#include "MoveComponent.h"
#include "TriggerComponent.h"
#include "TextureRenderer.h"
#include "Transform.h"
#include "VelocityComponent.h"

#include "GameObjectStorage.h"
#include "ObserverComponent.h"
#include "PengoEvents.h"
#include "SpriteRenderer.h"


DiamondBlock::DiamondBlock() : GameObject()
{
	SetTag("DiamondBlock");


	const auto boxCollider = AddComponent<BoxCollider>();
	boxCollider->SetColliderSize(m_SpriteSize);

	const auto triggerComponent = AddComponent<TriggerComponent>();
	triggerComponent->SetColliderSize(m_TriggerSize);

	const auto texture = AddComponent<TextureRenderer>();
	const auto spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->SetSpriteSize(m_SpriteSize);
	spriteRenderer->SetTexture("DiamondBlock.png");
	spriteRenderer->SetFrameTime(0.2f);
	spriteRenderer->Pause();

	for (int i = 0; i < m_Frames; ++i)
	{
		spriteRenderer->AddSpriteFrame({ i * 16,0 }, MovementDirection::None);
		spriteRenderer->AddSpriteFrame({ i * 16,0 }, MovementDirection::Left);
		spriteRenderer->AddSpriteFrame({ i * 16,0 }, MovementDirection::Right);
		spriteRenderer->AddSpriteFrame({ i * 16,0 }, MovementDirection::Up);
		spriteRenderer->AddSpriteFrame({ i * 16,0 }, MovementDirection::Down);
	}


	AddComponent<GameObjectStorage>();
	AddComponent<DirectionComponent>()->SetDirection({ 1,0 });
	AddComponent<VelocityComponent>()->SetVelocity(80);
	AddComponent<MoveComponent>()->SetCanMove(false);
	AddComponent<ObserverComponent>()->AddObserver(std::make_shared<PengoEvent>());
}

DiamondBlock::~DiamondBlock()
{

}


void DiamondBlock::Update()
{
	GameObject::Update();
	if (m_IsInARow)
	{
		m_InARowAnimationTimer -= TimeM::GetInstance().GetDeltaTimeM();
		GetComponent<SpriteRenderer>()->Play();


		if (m_InARowAnimationTimer <= 0.f)
		{
			GetComponent<ObserverComponent>()->NotifyObserver(this, GameEvent::DiamondBlockThreeInARow);
		}
	}
}

void DiamondBlock::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	GameObject::OnCollision(other, isTrigger, isSenderTrigger);
	const auto& collidingBoxes = GetCollidingObjects();


	//Collect the colliding blocks of THIS diamond block
	//This will be 1 or 2 blocks
	for (const auto& gameOBJ : collidingBoxes)
	{
		if (gameOBJ->GetTag() == GetTag() && gameOBJ != this)
		{
			m_CollidingDiamonds.emplace(dynamic_cast<DiamondBlock*>(gameOBJ));
		}
	}

	//Only do the rest of the check on the middle block (The one that will have 2 collisions)
	if (m_CollidingDiamonds.size() > 1)
	{
		for (const auto block : m_CollidingDiamonds)
		{
			block->SetIsInARow(true);
		}
		m_IsInARow = true;

	}


	if (isTrigger) return;
	if (isSenderTrigger) return;

	//Stop the block after being fired
	const auto moveComp = GetComponent<MoveComponent>();
	if (moveComp->CanMove())
	{
		moveComp->ResetMovement();
		moveComp->SetCanMove(false);
	}
}