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
#include "CountdownComponent.h"
#include "GhostComponent.h"
#include "TriggerComponent.h"
#include "TeleportComponent.h"

Ghost::Ghost() : m_pGameObject{ new GameObject() }
{
	//Texture Component
	const auto textureRenderer = m_pGameObject->AddComponent<TextureRenderer>();

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

	//Move Component
	const auto move = m_pGameObject->AddComponent<MoveComponent>();
	move->SetTunnelingMultiplier(1.1f);

	//Direction Component
	const auto direction = m_pGameObject->AddComponent<DirectionComponent>();
	direction->SetDirection({ 1,0 });

	//Velocity Component
	const auto velocity = m_pGameObject->AddComponent<VelocityComponent>();
	velocity->SetVelocity(50.f);


	//Collider Component
	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 10,10 });
	collider->SetColliderOffset({ 3,3 });

#ifdef _DEBUG
	collider->DebugRender(true);
#endif // _DEBUG


	//Trigger Component
	const auto trigger = m_pGameObject->AddComponent<TriggerComponent>();
	trigger->SetColliderSize({ 6, 6 });
	trigger->SetColliderOffset({ 5,5 });
	trigger->SetOffsetMultiplier(4.f);

#ifdef _DEBUG
	trigger->DebugRender(true);
#endif // _DEBUG

	//Transform Component
	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ 68,100 });

	//Storage for pacMan
	m_pGameObject->AddComponent<GameObjectStorage>();

	//Timer Component
	const auto countDown = m_pGameObject->AddComponent<CountdownComponent>();

	//Ghost Component
	const auto Ghost = m_pGameObject->AddComponent<GhostComponent>();
	//State Component
	const auto state = m_pGameObject->AddComponent<StateComponent>();



	Ghost->SetupStates();

	//Teleport Component
	m_pGameObject->AddComponent<TeleportComponent>();
}