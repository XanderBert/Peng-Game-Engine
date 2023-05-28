#include "SnowBeeState.h"

#include "IceBlockTrigger.h"
#include "PengoIceBlockTrigger.h"
#include "SnowBee.h"
#include "SpriteRenderer.h"

//
//-- Spawning -
//
SnowBeeState* SnowBeeSpawningState::HandleInput()
{
	if (const auto baseState = SnowBeeState::HandleInput()) { return baseState; }

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		if (spriteRenderer->IsAnimationFinished())
		{
			return new SnowBeeMovingState{ m_pActor };
		}
	}

	return nullptr;
}

void SnowBeeSpawningState::Update()
{

}

void SnowBeeSpawningState::OnCollision(GameObject* other)
{
	SnowBeeState::OnCollision(other);
}

void SnowBeeSpawningState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		m_pActor->SetDirection({ 0, 0 });
		spriteRenderer->SetOffset({ 0,0 });
		spriteRenderer->Play();
		spriteRenderer->SetFrameTime(0.2f);
	}
}


//
//-- Moving -
//
SnowBeeState* SnowBeeMovingState::HandleInput()
{
	if (const auto baseState = SnowBeeState::HandleInput()) { return baseState; }
	return nullptr;
}

void SnowBeeMovingState::Update()
{
	Move();
}

void SnowBeeMovingState::OnCollision(GameObject* other)
{
	SnowBeeState::OnCollision(other);
	StopMovement();
	ChangeMovement();
}

void SnowBeeMovingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		m_pActor->SetDirection({ 1, 0 });
		spriteRenderer->SetOffset({ 0,16 });
		spriteRenderer->SetFrameTime(0.4f);
	}
}

//
//-- Attacking
//
SnowBeeState* SnowbeeAttackingState::HandleInput()
{
	if (const auto baseState = SnowBeeState::HandleInput()) { return baseState; }
	return nullptr;
}

void SnowbeeAttackingState::Update()
{
}

void SnowbeeAttackingState::OnCollision(GameObject* other)
{

	SnowBeeState::OnCollision(other);
	StopMovement();
	ChangeMovement();
}

void SnowbeeAttackingState::OnEnter()
{
}


//
//-- Dying -
//
SnowBeeState* SnowBeeDyingState::HandleInput()
{
	if (const auto baseState = SnowBeeState::HandleInput()) { return baseState; }
	return nullptr;
}

void SnowBeeDyingState::Update()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		if (spriteRenderer->IsAnimationFinished())
		{
			m_pActor->MarkForDeletion();
		}
	}
}

void SnowBeeDyingState::OnCollision(GameObject* other)
{
	SnowBeeState::OnCollision(other);
}

void SnowBeeDyingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		//Set Movement Direction the same as the Incoming Movement Direction of the Iceblock
		const auto iceBlockVelocity = dynamic_cast<SnowBee*>(m_pActor)->GetHittedIceBlock()->GetFireDirection();
		spriteRenderer->SetMovementDirection(-iceBlockVelocity);
		spriteRenderer->SetOffset({ 0,64 });
		spriteRenderer->SetFrameTime(0.2f);
		spriteRenderer->SetAnimationFrame(0);
	}
}




//
//
//-- BASE STATE --
//
//
SnowBeeState* SnowBeeState::HandleInput()
{
	if (m_IsHit)
	{
		return new SnowBeeDyingState(m_pActor);
	}

	return nullptr;
}

void SnowBeeState::OnCollision(GameObject* other)
{
	if (const auto iceBlock = dynamic_cast<IceBlock*>(other))
	{
		if (iceBlock->IsMoving())
		{
			m_IsHit = true;
			dynamic_cast<SnowBee*>(m_pActor)->SetHittedIceBlock(iceBlock);
		}
	}
}

void SnowBeeState::ChangeMovement()
{
	const auto snowBee = dynamic_cast<SnowBee*>(m_pActor);

	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator

	const auto oldDirection = snowBee->GetDirection();
	auto newDirection = oldDirection;

	// Generate a new direction until it is different from the old direction
	while (newDirection == oldDirection)
	{
		// Generate a random integer between 0 and 3
		const int numQuarterTurns = std::rand() % 4;

		newDirection = oldDirection;

		// Perform the quarter turns
		for (int i = 0; i < numQuarterTurns; ++i)
		{
			const float temp = newDirection.x;
			newDirection.x = -newDirection.y;
			newDirection.y = temp;
		}
	}

	snowBee->SetDirection(newDirection);
}


void SnowBeeState::Move()
{
	const auto snowBee = dynamic_cast<SnowBee*>(m_pActor);

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		if (const auto transform = m_pActor->GetComponent<Transform>())
		{
			//Get Position
			const auto pos = transform->GetWorldPosition();

			//Calculate new position
			const glm::vec2 newPos = pos + snowBee->GetDirection() * snowBee->GetVelocity() * TimeM::GetInstance().GetDeltaTimeM();

			//Set new position
			transform->SetWorldPosition(newPos);
		}

		//Set movement Direction
		spriteRenderer->SetMovementDirection(snowBee->GetDirection());
	}
}

void SnowBeeState::StopMovement()
{
	if (const auto transform = m_pActor->GetComponent<Transform>())
	{
		const auto snowBee = dynamic_cast<SnowBee*>(m_pActor);
		transform->SetWorldPosition(transform->GetLastWorldPosition() + (-snowBee->GetDirection() * m_TunnelingMultiplier));
	}
}
