#include "Pengo.h"
#include "BoxCollider.h"
#include "Color.h"
#include "Controller.h"
#include "Controller.h"
#include "DirectionComponent.h"
#include "IceBlock.h"
#include "ObserverComponent.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "PengoEvents.h"
#include "PengoState.h"
#include "PlayerCommands.h"
#include "InputComponent.h"
#include "controllerComponent.h"
#include "Controller.h"
#include "GameObjectStorage.h"
#include "TriggerComponent.h"


Pengo::Pengo() : GameObject()
{
	//When Pengo is using a controller component, Somehow the Execute event (move) gets triggered twice per frame.
	//This should not be because there is 1 update trigger and no loop triggering the event?
	//Test if it is exactly a 2:1 ratio -> It is exatly a 2:1 ratio
	//This means that there are really 2 triggers to the execute event per frame.
	//So there is no synchronization issue due to concurrency.
	//Right now its hacked to work by dividing the velocity by 2.
	//This needs to be fixed (in the future).

	SetTag("Pengo");

	//Direction Component
	const auto directionComponent = AddComponent<DirectionComponent>();
	directionComponent->SetDirection({ 1,0 });


	//Trigger Component
	const auto triggerComponent = AddComponent<TriggerComponent>();
	triggerComponent->DebugRender(true);
	triggerComponent->SetColliderSize({ 10,10 });// -> It is self colliding???
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
	boxCollision->SetColliderSize({ 13,13 });
	boxCollision->DebugRender(true);

	//GameObject Storage Component
	AddComponent<GameObjectStorage>();

	//Audio Component Needs to be made?
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(0, "Notification.wav");

	const auto observerComponent = AddComponent<ObserverComponent>();
	observerComponent->AddObserver(std::make_shared<PengoEvent>());

	m_pState = new MovingState(this);
	AddComponent<VelocityComponent>()->SetVelocity(200);
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
	if (dynamic_cast<Pengo*>(other)) { return; }

	m_pState->OnCollision(other, isTrigger, isSenderTrigger);


	if (isSenderTrigger) return;
	if (isTrigger) return;

	//If is hitted by moving ice block or by enemy go into dying state


	//if (dynamic_cast<IceBlock*>(other))
	//{
	//	GetComponent<ObserverComponent>()->NotifyObserver(this, GameEvent::CollidingWithIce);
	//	return;
	//}

	StopMovement();
}

void Pengo::StopMovement() const
{
	const auto transform = GetComponent<Transform>();
	const auto direction = GetComponent<DirectionComponent>()->GetDirection();

	//Tunneling still occurs with this method.
	transform->SetWorldPosition(transform->GetLastWorldPosition() + (-direction * m_TunnelingMultiplier));


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