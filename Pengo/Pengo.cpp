#include "Pengo.h"
#include "BoxCollider.h"
#include "IceBlock.h"
#include "IceBlockTrigger.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "PengoEvents.h"
#include "PengoIceBlockTrigger.h"
#include "PengoState.h"


Pengo::Pengo() : GameActor()
{
	m_pIceBlockTrigger = new PengoIceBlockTrigger(this);


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
	boxCollision->SetColliderSize({ 16,16 });

	ServiceLocator::GetInstance().AudioService.GetService().AddSound(0, "Notification.wav");

	AddObserver(std::make_shared<PengoEvent>());

	m_pState = new MovingState(this);
}

Pengo::~Pengo()
{
	delete m_pState;
}

void Pengo::Move(const glm::vec2& direction)
{
	GameActor::Move(direction);
}

void Pengo::Attack()
{
}

void Pengo::Update()
{
	GameActor::Update();
	UpdateState();

}

void Pengo::LateUpdate()
{
	GameActor::LateUpdate();
}

void Pengo::OnCollision(GameObject* other)
{
	if (dynamic_cast<PengoIceBlockTrigger*>(other)) { return; }

	GameActor::OnCollision(other);
	m_pState->OnCollision(other);

	if (dynamic_cast<IceBlockTrigger*>(other))
	{
		NotifyObserver(this, GameEvent::CollidingWithIce);
		return;
	}

	StopMovement();
}

void Pengo::StopMovement() const
{
	const auto transform = GetComponent<Transform>();


	//Tunneling still occurs with this method.
	if (const auto spriteRenderer = GetComponent<SpriteRenderer>())
	{
		const auto movementDirection = spriteRenderer->GetMovementDirectionVector();
		transform->SetWorldPosition(transform->GetLastWorldPosition() + (-movementDirection * m_TunnelingMultiplier));
	}

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