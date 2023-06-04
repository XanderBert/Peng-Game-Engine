#include "DiamondBlock.h"
#include  "BoxCollider.h"
#include "DirectionComponent.h"
#include "MoveComponent.h"
#include "TriggerComponent.h"
#include "TextureRenderer.h"
#include "Transform.h"
#include "VelocityComponent.h"

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
	AddComponent<VelocityComponent>()->SetVelocity(30);
	AddComponent<MoveComponent>()->SetCanMove(false);
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

	m_DiamondBlockCount = 0;

	if (isTrigger) return;
	if (isSenderTrigger) return;

	//Stop the block after being fired
	const auto moveComp = GetComponent<MoveComponent>();
	if (moveComp->CanMove())
	{
		moveComp->ResetMovement();
		moveComp->SetCanMove(false);


		for (const auto& box : GetComponent<BoxCollider>()->GetCollidingBoxes())
		{
			if (box->GetGameObject() != this)
				if (box->GetGameObject()->GetTag() == "DiamondBlock")
				{


					++m_DiamondBlockCount;

					std::cout << m_DiamondBlockCount + dynamic_cast<DiamondBlock*>(box->GetGameObject())->GetDiamondBlockCount() << std::endl;
				}
		}

		//ServiceLocator::GetInstance().CollisionManager.GetService().
	}



}
