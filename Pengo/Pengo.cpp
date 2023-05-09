#include "Pengo.h"

#include "BoxCollider.h"
#include "IceBlock.h"
#include "SpriteRenderer.h"
#include "Wall.h"
#include "WallManager.h"

Pengo::Pengo() : GameActor()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	textureRenderer->SetTexture("Pengo.png");

	const auto spriteRenderer{ AddComponent<SpriteRenderer>() };
	spriteRenderer->SetSpriteSize({ 16,16 });

	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Right);

	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize({16,16});
	//boxCollision->DebugRender(true);
}

Pengo::~Pengo()
{
}

void Pengo::Attack()
{
	if(m_IsCollidingWithIce)
	{
		auto block = dynamic_cast<IceBlock*>(m_CollidingObject);

		//block.TakeAttack()
	}
}

void Pengo::Update()
{
	GameActor::Update();

	m_IsCollidingWithIce = false;
	m_CollidingObject = nullptr;
}

void Pengo::OnCollision(GameObject* other)
{
	m_CollidingObject = other;


	if(dynamic_cast<Wall*>(other))
	{
		StopMovement();
	}

	if (dynamic_cast<IceBlock*>(other))
	{
		StopMovement();
		m_IsCollidingWithIce = true;

		//When space is pressed. and collision is active.
		//Make bool member in pengo isColliding with ice.
		//this function will set that to true.
		
		//Fire -> will check if if bool is true
		//Move ICE BLOCK make function for it. if it collides with wall/ice block. stop moving
		//when it cannot move in that direction it gets destroyed

	}
}

void Pengo::StopMovement() const
{
	const auto transform = GetComponent<Transform>();
	transform->SetWorldPosition(transform->GetLastWorldPosition());
}

