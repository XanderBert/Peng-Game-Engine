#include "Pengo.h"
#include "BoxCollider.h"
#include "IceBlock.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "Wall.h"
#include "WallManager.h"
#include "PlayerState.h"
#include "PengoEvents.h"
#include "TimeM.h"


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


	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize({ 16,16 });
	//boxCollision->DebugRender(true);

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

	//if (m_CollidingObject)
	//{
	//	m_TimeUntilCollisionForget -= TimeM::GetInstance().GetDeltaTimeM();
	//	if (m_TimeUntilCollisionForget <= 0.f)
	//	{
	//		ResetCollision();
	//	}
	//}


}

void Pengo::LateUpdate()
{
	GameActor::LateUpdate();
}

void Pengo::OnCollision(GameObject* other)
{
	GameActor::OnCollision(other);

	//Set the colliding object
	//ResetCollision();

	//std::cout << "Pengo collided with " << other << std::endl;

	//Call the OnCollision of the current state
	m_pState->OnCollision();


	if (dynamic_cast<Wall*>(other))
	{
		StopMovement();
	}

	if (dynamic_cast<IceBlock*>(other))
	{
		NotifyObserver(this, GameEvent::CollidingWithIce);
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

//void Pengo::ResetCollision()
//{
//	m_TimeUntilCollisionForget = 0.3f;
//	m_CollidingObject = nullptr;
//}

void Pengo::UpdateState()
{
	if (const auto newState = m_pState->HandleInput())
	{
		delete m_pState;
		m_pState = newState;
	}
	m_pState->Update();
}

