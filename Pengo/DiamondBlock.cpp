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


DiamondBlock::DiamondBlock() : GameObject()
{
	SetTag("DiamondBlock");


	const auto boxCollider = AddComponent<BoxCollider>();
	boxCollider->SetColliderSize(m_SpriteSize);

	const auto triggerComponent = AddComponent<TriggerComponent>();
	triggerComponent->SetColliderSize(m_TriggerSize);

	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("DiamondBlock.png");

	GetComponent<Transform>()->SetWorldPosition({ 77,70 });

	//When being hit
	//Direction Should be set as the same as the player
	//MoveComponent should be set to true

	AddComponent<DirectionComponent>()->SetDirection({ 0,0 });
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

	//Somehow Check if there are 3 diamond blocks next to each other

	//Make a IsColliding with function?
	//On a collision get all the colliding objects, read their tag, if i do this for every diamond block, then
	//1 block should have 2 collisions, and the other 2 should have 1 collision

	//Where would i store this and check this?
	//In the level manager? that would be the most logical place to do this

}

void DiamondBlock::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	GameObject::OnCollision(other, isTrigger, isSenderTrigger);

	if (isTrigger) return;
	if (isSenderTrigger) return;

	//Stop the block after being fired
	const auto moveComp = GetComponent<MoveComponent>();
	if (moveComp->CanMove())
	{
		moveComp->ResetMovement();
		moveComp->SetCanMove(false);
	}


	const auto& collidingBoxes = GetCollidingObjects();
	std::set<GameObject*> diamondBlocks;

	//Collect the colliding blocks of THIS diamond block
	//This will be 1 or 2 blocks
	for (const auto& gameOBJ : collidingBoxes)
	{
		if (gameOBJ->GetTag() == GetTag() && gameOBJ != this)
		{
			diamondBlocks.emplace(gameOBJ);
		}
	}

	//Only do the rest of the check on the middle block (The one that will have 2 collisions)
	if (diamondBlocks.size() > 1)
	{
		GetComponent<ObserverComponent>()->NotifyObserver(this, GameEvent::DiamondBlockThreeInARow);
		for (const auto block : diamondBlocks) block->MarkForDeletion();
		diamondBlocks.clear();
		MarkForDeletion();
	}
}





