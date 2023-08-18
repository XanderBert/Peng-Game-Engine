#include "PacManState.h"
#include "CountdownComponent.h"
#include "GameObjectStorage.h"
#include "MoveComponent.h"
#include "PacDotComponent.h"
#include "PacManComponent.h"
#include "PowerUpComponent.h"
#include "ScoreComponent.h"
#include "SpriteRenderer.h"
#include "WallComponent.h"
#include "PacManEventObserver.h"

//MOVE
//
//
PacManMoveState::PacManMoveState(GameObject* object) : State(object)
{
	OnEnter();
}

State* PacManMoveState::HandleInput()
{
	if (m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
	{
		return new PacManIdleState(m_pActor);
	}

	return nullptr;
}

void PacManMoveState::Update()
{
	const auto timer = m_pActor->GetComponent<CountdownComponent>();

	if (m_pActor->GetComponent<MoveComponent>()->IsMovingThisFrame())
	{
		timer->ResetTime();
		timer->Pause();
	}
	else
	{
		timer->Play();
	}

}

void PacManMoveState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{

	if (other->GetComponent<PacDotComponent>())
	{
		m_pActor->GetComponent<PacManComponent>()->Notify(GameEvent::PacDotEaten, m_pActor);
		other->MarkForDeletion();
	}

	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
	}

	if (other->GetComponent<PowerUpComponent>() && !isSenderTrigger && !isTrigger)
	{
		//Alert All Ghost to change state
		m_pActor->GetComponent<PacManComponent>()->Notify(GameEvent::PowerUpEaten, m_pActor);
		other->MarkForDeletion();
	}
}

void PacManMoveState::OnEnter()
{

	if (const auto timer = m_pActor->GetComponent<CountdownComponent>())
	{
		timer->SetTime(0.1f);
		timer->Pause();
	}

	m_pActor->GetComponent<SpriteRenderer>()->Play();
}



//IDLE
//
//
PacManIdleState::PacManIdleState(GameObject* object) : State(object)
{
	OnEnter();
}

State* PacManIdleState::HandleInput()
{

	if (m_pActor->GetComponent<MoveComponent>()->IsMovingThisFrame())
	{
		return new PacManMoveState(m_pActor);
	}

	return nullptr;
}

void PacManIdleState::Update()
{
}

void PacManIdleState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
}

void PacManIdleState::OnEnter()
{
	m_pActor->GetComponent<SpriteRenderer>()->Pause();
	m_pActor->GetComponent<SpriteRenderer>()->SetTexture("PacMan.png");
}








//Only in Vs Mode
//
//
PacManFrightenedState::PacManFrightenedState(GameObject* object) : State(object)
{
	OnEnter();
}

State* PacManFrightenedState::HandleInput()
{
	if (m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
	{
		return new PacManIdleState(m_pActor);
	}
	return nullptr;
}

void PacManFrightenedState::Update()
{
}

void PacManFrightenedState::OnCollision(GameObject* other, bool /*isTrigger*/, bool isSenderTrigger)
{
	if (other->GetComponent<PacDotComponent>())
	{
		m_pActor->GetComponent<PacManComponent>()->Notify(GameEvent::PacDotEaten, m_pActor);
		other->MarkForDeletion();
	}

	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
	}
}

void PacManFrightenedState::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Die because the other pacman ate you
	if (other->GetComponent<PacManComponent>() && other != m_pActor && !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<PacManComponent>()->Notify(GameEvent::PacManDied, m_pActor);
	}
}

void PacManFrightenedState::OnEnter()
{
	m_pActor->GetComponent<SpriteRenderer>()->SetTexture("PacManFrightened.png");


	if (const auto timer = m_pActor->GetComponent<CountdownComponent>())
	{
		timer->SetTime(3.5f);
		timer->Play();
	}

	m_pActor->GetComponent<SpriteRenderer>()->Play();
	m_pActor->GetComponent<SpriteRenderer>()->SetFrameTime(0.2f);
}
