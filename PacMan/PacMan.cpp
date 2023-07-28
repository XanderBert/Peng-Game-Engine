#include "PacMan.h"
#include "DirectionComponent.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "MoveComponent.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "StateComponent.h"
#include "VelocityComponent.h"
#include "CountdownComponent.h"
#include "BoxCollider.h"
#include "PacManComponent.h"
#include "TeleportComponent.h"
#include "TriggerComponent.h"

PacMan::PacMan() : m_pGameObject{new GameObject() }
{
	//Texture Component
	const auto textureRenderer{ m_pGameObject->AddComponent<TextureRenderer>() };
	textureRenderer->SetTexture("PacMan.png");

	//Sprite Component
	const auto spriteRenderer{ m_pGameObject->AddComponent<SpriteRenderer>() };
	spriteRenderer->SetSpriteSize({ 16,16 });

	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Right);

	spriteRenderer->AddSpriteFrame({ 0,16 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 16,16 }, MovementDirection::Left);

	spriteRenderer->AddSpriteFrame({ 0,32 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 16,32 }, MovementDirection::Up);

	spriteRenderer->AddSpriteFrame({ 0,48 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 16,48 }, MovementDirection::Down);

	spriteRenderer->SetFrameTime(0.05f);

	//Direction Component
	const auto directionComponent = m_pGameObject->AddComponent<DirectionComponent>();
	directionComponent->SetDirection({ 1,0 });


	//Move Component
	m_pGameObject->AddComponent<MoveComponent>()->SetTunnelingMultiplier(1.f);


	//Velocity Component
	const auto velocityComponent = m_pGameObject->AddComponent<VelocityComponent>();
	velocityComponent->SetVelocity(200.f);


	//Input Component
	const auto inputComp = m_pGameObject->AddComponent<InputHandler>();

	//State Component
	const auto stateComponent = m_pGameObject->AddComponent<StateComponent>();
	stateComponent->SetState(new PacManIdleState(GetPacMan()));

	//Countdown Component
	const auto timerComponent = m_pGameObject->AddComponent<CountdownComponent>();

	//Collider Component
	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 11, 11 });
	collider->SetColliderOffset({ 1,1 });
#ifdef _DEBUG
	collider->DebugRender(true);
#endif // DEBUG

	//Trigger Component
	const auto trigger = m_pGameObject->AddComponent<TriggerComponent>();
	trigger->SetColliderSize({ 6, 6 });
	trigger->SetColliderOffset({ 3,3 });
	trigger->SetOffsetMultiplier(2.f);

#ifdef _DEBUG
	trigger->DebugRender(true);
#endif // _DEBUG

	//PacMan Component



	const auto pacMan = m_pGameObject->AddComponent<PacManComponent>();
	//pacMan->SetLives(3);

	//Transform Component
	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ 10,10 });

	//Teleport Component
	m_pGameObject->AddComponent<TeleportComponent>();
}
