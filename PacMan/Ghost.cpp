#include "Ghost.h"

#include "DirectionComponent.h"
#include "GameObject.h"
#include "GhostState.h"
#include "MoveComponent.h"
#include "SpriteRenderer.h"
#include "StateComponent.h"
#include "TextureRenderer.h"
#include "VelocityComponent.h"
#include "BoxCollider.h"
#include "GameObjectStorage.h"
#include "Transform.h"

Ghost::Ghost() : m_pGameObject{ new GameObject() }
{
	//Texture Component
	const auto textureRenderer = m_pGameObject->AddComponent<TextureRenderer>();
	textureRenderer->SetTexture("GhostRed.png");

	//Sprite Component
	const auto spriteRenderer = m_pGameObject->AddComponent<SpriteRenderer>();

	spriteRenderer->SetSpriteSize({ 16,16 });

	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Right);

	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);

	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);

	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Down);


	//State Component
	const auto state = m_pGameObject->AddComponent<StateComponent>();
	state->SetState(new GhostMoveState(m_pGameObject));

	//Move Component
	const auto move = m_pGameObject->AddComponent<MoveComponent>();
	move->SetTunnelingMultiplier(1.1f);
	move->SetCanMove(true);

	//Direction Component
	const auto direction = m_pGameObject->AddComponent<DirectionComponent>();
	direction->SetDirection({1,0});

	//Velocity Component
	const auto velocity = m_pGameObject->AddComponent<VelocityComponent>();
	velocity->SetVelocity(100.f);


	//Collider Component
	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 12,12 });

	//Transform Component
	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ 50,50 });

	//Storage for pacMan
	m_pGameObject->AddComponent<GameObjectStorage>();
}
