#include "Pengo.h"
#include "BoxCollider.h"
#include "DirectionComponent.h"
#include "ObserverComponent.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "PengoEvents.h"
#include "PengoState.h"
#include "PlayerCommands.h"
#include "GameObjectStorage.h"
#include "MoveComponent.h"
#include "SnowBee.h"
#include "TriggerComponent.h"
#include "PlayerState.h"

Pengo::Pengo() : GameObject()
{
	SetTag("Pengo");

	//ObserverComponent
	AddComponent<ObserverComponent>()->AddObserver(m_pObserver);

	//Direction Component
	const auto directionComponent = AddComponent<DirectionComponent>();
	directionComponent->SetDirection({ 1,0 });


	//Trigger Component
	const auto triggerComponent = AddComponent<TriggerComponent>();
	triggerComponent->SetColliderSize({ 4,8 });
	triggerComponent->SetOffsetMultiplier({ 10 });
	triggerComponent->SetColliderOffset({ 3,3 });


	//Texture Component
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	textureRenderer->SetTexture("Pengo.png");


	//Sprite Component
	const auto spriteRenderer{ AddComponent<SpriteRenderer>() };
	spriteRenderer->SetSpriteSize({ 16,16 });

	//Is used for attacking, moving and idle
	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Right);

	//is Used for dying
	spriteRenderer->AddSpriteFrame({ 0,32 }, MovementDirection::None);
	spriteRenderer->AddSpriteFrame({ 16,32 }, MovementDirection::None);

	//Box Collider Component
	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize({ 11,11 });
	boxCollision->SetColliderOffset({ 3,3 });
	//boxCollision->DebugRender(true);


	//GameObject Storage Component
	AddComponent<GameObjectStorage>();

	//Move Component
	AddComponent<MoveComponent>();

	//Audio Component Needs to be made?
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(0, "Notification.wav");

	const auto observerComponent = AddComponent<ObserverComponent>();
	observerComponent->AddObserver(std::make_shared<PengoEvent>());

	AddComponent<VelocityComponent>()->SetVelocity(200);
	m_pState = new MovingState(this);
}

Pengo::~Pengo()
{
	delete m_pState;
}


void Pengo::Update()
{
	GameObject::Update();
	UpdateState();
}

void Pengo::LateUpdate()
{
	GameObject::LateUpdate();
}

void Pengo::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	if (other->GetTag() == "Pengo") { return; }

	m_pState->OnCollision(other, isTrigger, isSenderTrigger);

	if (isSenderTrigger) return;

	//Dont Collide With Concussed  or Dying SnowBee
	if (const auto snowBee = dynamic_cast<SnowBee*>(other))
	{

		return;

	}

	if (isTrigger) return;
	GetComponent<MoveComponent>()->ResetMovement();

}

void Pengo::UpdateState()
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

