#include "SnowBee.h"

#include "GameObjectStorage.h"
#include "IceBlock.h"
#include "MoveComponent.h"
#include "Pengo.h"
#include "ServiceLocator.h"
#include "SnowBeeState.h"
#include "SpriteRenderer.h"
#include "Transform.h"

SnowBee::SnowBee()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	textureRenderer->SetTexture("SnowBee.png");

	const auto spriteRenderer{ AddComponent<SpriteRenderer>() };
	spriteRenderer->SetSpriteSize(m_SpriteSize);

	// All other animations
	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Right);


	//Spawinging Animation
	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::None);


	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize(m_SpriteSize);

	GetComponent<Transform>()->SetWorldPosition({ 250,250 });

	m_pState = new SnowBeeSpawningState(this);

	AddComponent<VelocityComponent>()->SetVelocity(40);
	AddComponent<DirectionComponent>()->SetDirection({ 0,0 });
	AddComponent<MoveComponent>();
	AddComponent<GameObjectStorage>();
}

SnowBee::~SnowBee()
{
	delete m_pState;
}

void SnowBee::Update()
{
	GameObject::Update();
	UpdateState();
}

void SnowBee::LateUpdate()
{
	GameObject::LateUpdate();
}

void SnowBee::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	m_pState->OnCollision(other, isTrigger, isSenderTrigger);
	if (isTrigger)
	{
		return;
	}

}

void SnowBee::UpdateState()
{
	if (const auto newState = m_pState->HandleInput())
	{
		if (newState)
		{
			delete m_pState;
			m_pState = newState;
		}
	}
	m_pState->Update();
}