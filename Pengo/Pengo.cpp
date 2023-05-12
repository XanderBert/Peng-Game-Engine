#include "Pengo.h"
#include "BoxCollider.h"
#include "IceBlock.h"
#include "ServiceLocator.h"
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

	spriteRenderer->SetActionOffset({ 0,0 }, Action::Move);
	spriteRenderer->SetActionOffset({ 0,16 }, Action::Attack);

	

	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize({ 16,16 });
	//boxCollision->DebugRender(true);

	ServiceLocator::GetInstance().AudioService.GetService().AddSound(0, "Notification.wav");

}

Pengo::~Pengo()
{
}

void Pengo::Move(const glm::vec2& direction)
{
	if (const auto spriteRenderer = GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetAction(Action::Move);
	}

	GameActor::Move(direction);
	ResetCollision();
}

void Pengo::Attack()
{
	ServiceLocator::GetInstance().AudioService.GetService().Play(0);

	if (const auto spriteRenderer = GetComponent<SpriteRenderer>())
	{
		if (m_IsCollidingWithIce)
		{
			dynamic_cast<IceBlock*>(m_CollidingObject)->MoveIceBlock(spriteRenderer->GetMovementDirection());
		}

		spriteRenderer->SetAction(Action::Attack);
	}
}

void Pengo::Update()
{
	GameActor::Update();
}

void Pengo::LateUpdate()
{
	GameActor::LateUpdate();
}

void Pengo::OnCollision(GameObject* other)
{
	m_CollidingObject = other;


	if (dynamic_cast<Wall*>(other))
	{
		StopMovement();
	}

	if (dynamic_cast<IceBlock*>(other))
	{
		m_IsCollidingWithIce = true;
		StopMovement();

		//TODO ONLY when it cannot move in that direction it gets destroyed!!!
		//Now it gets destroyed when it collides with anything on the first attack

	}
}

void Pengo::StopMovement() const
{
	const auto transform = GetComponent<Transform>();
	transform->SetWorldPosition(transform->GetLastWorldPosition());
}

void Pengo::ResetCollision()
{
	m_IsCollidingWithIce = false;
	m_CollidingObject = nullptr;
}

