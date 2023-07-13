#include "PacMan.h"

#include "DirectionComponent.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "MoveComponent.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "MoveCommand.h"
#include "StateComponent.h"
#include "VelocityComponent.h"
#include "CountdownComponent.h"
#include "BoxCollider.h"

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

	//Direction Component
	const auto directionComponent = m_pGameObject->AddComponent<DirectionComponent>();
	directionComponent->SetDirection({ 1,0 });


	//Move Component
	m_pGameObject->AddComponent<MoveComponent>();


	//Velocity Component
	const auto velocityComponent = m_pGameObject->AddComponent<VelocityComponent>();
	velocityComponent->SetVelocity(1200.f);


	//Input Component
	const auto inputComp = m_pGameObject->AddComponent<InputHandler>();

	//State Component
	const auto stateComponent = m_pGameObject->AddComponent<StateComponent>();
	stateComponent->SetState(new PacManIdleState(GetPacMan()));

	//Countdown Component
	const auto timerComponent = m_pGameObject->AddComponent<CountdownComponent>();

	//Collider Comonent
	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 16, 16 });
	collider->SetColliderOffset({ -1,-1 });


#ifdef _DEBUG
	collider->DebugRender(true);
#endif // DEBUG

	
}