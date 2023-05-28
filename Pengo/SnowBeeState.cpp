#include "SnowBeeState.h"

#include "DirectionComponent.h"
#include "IceBlockTrigger.h"
#include "MoveComponent.h"
#include "PengoIceBlockTrigger.h"
#include "SnowBee.h"
#include "SpriteRenderer.h"
#include "VelocityComponent.h"

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
		spriteRenderer->SetOffset({ 0,0 });
		spriteRenderer->Play();
		spriteRenderer->SetFrameTime(0.2f);
	}
	if (const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		directionComponent->SetDirection({ 0, 0 });
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
	if(const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		directionComponent->SetDirection({ 1, 0 });
	}

	ChangeMovement();

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
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
		const auto iceBlockDirection = dynamic_cast<SnowBee*>(m_pActor)->GetHittedIceBlock()->GetComponent<DirectionComponent>()->GetDirection();

		if(const auto direction = m_pActor->GetComponent<DirectionComponent>())
		{
			direction->SetDirection(-iceBlockDirection);

			spriteRenderer->SetOffset({ 0,64 });
			spriteRenderer->SetFrameTime(0.2f);
			spriteRenderer->SetAnimationFrame(0);
		}
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
		if (iceBlock->GetComponent<MoveComponent>()->CanMove())
		{
			m_IsHit = true;
			dynamic_cast<SnowBee*>(m_pActor)->SetHittedIceBlock(iceBlock);
		}
	}
}

void SnowBeeState::ChangeMovement()
{
	if(const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator
		const glm::vec2 oldDirection{ directionComponent->GetDirection()};

		auto newDirection = oldDirection;

		// Generate a new direction until it is different from the old direction

		//TODO run on seperate thread?
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

			directionComponent->SetDirection(newDirection);
		}
	}
}


void SnowBeeState::Move()
{
	//const auto snowBee = dynamic_cast<SnowBee*>(m_pActor);

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		if (const auto transform = m_pActor->GetComponent<Transform>())
		{
			if(const auto direction = m_pActor->GetComponent<DirectionComponent>())
			{
				if(const auto velocity = m_pActor->GetComponent<VelocityComponent>())
				{
					//Get Position
					const auto pos = transform->GetWorldPosition();

					//Calculate new position
					const glm::vec2 newPos = pos + direction->GetDirection() * velocity->GetVelocity() * TimeM::GetInstance().GetDeltaTimeM();

					//Set new position
					transform->SetWorldPosition(newPos);
				}
				
			}
		}
	}
}

void SnowBeeState::StopMovement()
{
	if (const auto transform = m_pActor->GetComponent<Transform>())
	{
		if(const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
		{
			transform->SetWorldPosition(transform->GetLastWorldPosition() + (-directionComponent->GetDirection() * m_TunnelingMultiplier));
		}
	}
}
