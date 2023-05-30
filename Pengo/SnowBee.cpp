#include "SnowBee.h"

#include "IceBlock.h"
#include "IceBlockTrigger.h"
#include "MoveComponent.h"
#include "Pengo.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "TimeM.h"
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
	boxCollision->SetColliderSize({ 16,16 });

	GetComponent<Transform>()->SetWorldPosition({ 250,250 });

	m_pState = new SnowBeeSpawningState(this);

	AddComponent<VelocityComponent>()->SetVelocity(20);
	AddComponent<DirectionComponent>()->SetDirection({ 0,0 });
	AddComponent<MoveComponent>();

	//Snow Bee only plays the last 2 frames of the spawning animation.?
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

void SnowBee::OnCollision(GameObject* other)
{
	if (dynamic_cast<PengoIceBlockTrigger*>(other) || dynamic_cast<IceBlockTrigger*>(other))
	{
		return;
	}

	GameObject::OnCollision(other);
	m_pState->OnCollision(other);
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