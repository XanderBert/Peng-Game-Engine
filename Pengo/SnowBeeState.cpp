#include "SnowBeeState.h"
#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "IceBlock.h"
#include "MoveComponent.h"
#include "Pengo.h"
#include "SnowBee.h"
#include "SpriteRenderer.h"
#include "TriggerComponent.h"

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

void SnowBeeSpawningState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	SnowBeeState::OnCollision(other, isTrigger, isSenderTrigger);
}

void SnowBeeSpawningState::OnEnter()
{
	if (const auto moveComponent = m_pActor->GetComponent<MoveComponent>())
	{
		moveComponent->SetCanMove(false);
	}

	if (const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		directionComponent->SetDirection({ 0, 0 });
	}

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetOffset({ 0,0 });
		spriteRenderer->Play();
		spriteRenderer->SetFrameTime(0.3f);
	}

}


//
//-- Moving -
//
SnowBeeState* SnowBeeMovingState::HandleInput()
{
	if (const auto baseState = SnowBeeState::HandleInput()) { return baseState; }
	if (m_GoInAttackState)
	{
		return new SnowbeeAttackingState{ m_pActor };
	}
	return nullptr;
}

void SnowBeeMovingState::Update()
{
	m_TimeUntilAttack -= TimeM::GetInstance().GetDeltaTimeM();
	if (m_TimeUntilAttack <= 0)
	{
		m_GoInAttackState = true;
	}
}

void SnowBeeMovingState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	SnowBeeState::OnCollision(other, isTrigger, isSenderTrigger);

	if (isTrigger) return;
	ChangeMovement();

}

void SnowBeeMovingState::OnEnter()
{
	if (const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		directionComponent->SetDirection({ 1, 0 });
	}

	//ChangeMovement();

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetOffset({ 0,16 });
		spriteRenderer->SetFrameTime(0.4f);
	}


	if (const auto moveComponent = m_pActor->GetComponent<MoveComponent>())
	{
		moveComponent->SetCanMove(true);
	}
}

//
//-- Attacking
//
SnowBeeState* SnowbeeAttackingState::HandleInput()
{
	if (const auto baseState = SnowBeeState::HandleInput()) { return baseState; }
	if (m_GoInMovingState)
	{
		return new SnowBeeMovingState{ m_pActor };
	}

	return nullptr;
}

void SnowbeeAttackingState::Update()
{
	m_TimeUntilMoving -= TimeM::GetInstance().GetDeltaTimeM();
	if (m_TimeUntilMoving <= 0)
	{
		m_GoInMovingState = true;
	}
}

void SnowbeeAttackingState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	SnowBeeState::OnCollision(other, isTrigger, isSenderTrigger);
	if (isTrigger) return;

	if (other->GetTag() == "IceBlock")
	{
		other->GetComponent<SpriteRenderer>()->Play();
		m_pActor->GetComponent<GameObjectStorage>()->AddGameObjectToVector(other);
	}

	ChangeMovement();

}

void SnowbeeAttackingState::OnEnter()
{
	if (const auto moveComponent = m_pActor->GetComponent<MoveComponent>())
	{
		moveComponent->SetCanMove(true);
	}

	if (const auto spriterenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriterenderer->SetOffset({ 0,32 });
		spriterenderer->SetFrameTime(0.2f);
	}
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

void SnowBeeDyingState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
	//SnowBeeState::OnCollision(other, isTrigger);
}

void SnowBeeDyingState::OnEnter()
{
	//Set Movement Direction the same as the Incoming Movement Direction of the IceBlock
	//And Change the sprites to the dying sprites

	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		//Change the sprites
		spriteRenderer->SetOffset({ 0,64 });
		spriteRenderer->SetFrameTime(0.2f);
		spriteRenderer->SetAnimationFrame(0);

		//TODO DIfferantiate between enter bc of Ice or because of Concussion

		//Get the IceBlock
		if (const auto storage = m_pActor->GetComponent<GameObjectStorage>())
		{
			if (const auto iceBlock = storage->GetGameObject())
			{
				//Get the direction of the IceBlock
				if (const auto direction = iceBlock->GetComponent<DirectionComponent>())
				{
					//Get the SnowBee direction
					if (const auto SnowBeeirection = m_pActor->GetComponent<DirectionComponent>())
					{
						//Set the SnowBee direction to the opposite of the IceBlock direction
						SnowBeeirection->SetDirection(-direction->GetDirection());

						//Stop the Movment Of the SnowBee
						if (const auto moveComponent = m_pActor->GetComponent<MoveComponent>())
						{
							moveComponent->SetCanMove(false);
						}
					}
				}
			}
		}
	}
}



//CONCUSSED
//
//
SnowBeeState* SnowBeeConcussedState::HandleInput()
{
	if (m_GoInDyingState)
	{
		return new SnowBeeDyingState{ m_pActor };
	}

	if (m_ConcussedTime <= 0)
	{
		return new SnowBeeMovingState{ m_pActor };
	}
	return nullptr;
}

void SnowBeeConcussedState::Update()
{
	m_ConcussedTime -= TimeM::GetInstance().GetDeltaTimeM();
}

void SnowBeeConcussedState::OnCollision(GameObject* other, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
	//SnowBeeState::OnCollision(other, isTrigger);
	if (other->GetTag() == "Pengo")
		m_GoInDyingState = true;
}

void SnowBeeConcussedState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetOffset({ 0,80 });
		spriteRenderer->SetFrameTime(0.2f);
		spriteRenderer->SetAnimationFrame(0);
	}
	if (const auto moveComponent = m_pActor->GetComponent<MoveComponent>())
	{
		moveComponent->SetCanMove(false);
	}

	if (const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		directionComponent->SetDirection({ 0, 0 });
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

	if (m_IsConcussed)
	{
		return new SnowBeeConcussedState(m_pActor);
	}

	return nullptr;
}

void SnowBeeState::OnCollision(GameObject* other, bool isTrigger, bool /*isSenderTrigger*/)
{
	//If it collides with an active wall trigger.
	//Go in the concussed state

	if (other->GetTag() == "Wall")
	{
		if (isTrigger)
		{
			if (other->GetComponent<SpriteRenderer>()->IsPlaying())
			{
				m_IsConcussed = true;
			}
		}
	}



	//If it is an IceBlock it collided with
	if (other->GetTag() == "IceBlock")
	{
		//If it is one of the same objects that the snowbee attacked do nothing
		for (const auto iceBlock : m_pActor->GetComponent<GameObjectStorage>()->GetGameObjectsFromVector())
		{
			if (iceBlock == other)
			{
				return;
			}
		}

		//If te iceblock is in its it hitted state
		if (other->GetComponent<SpriteRenderer>()->IsPlaying())
		{
			m_IsHit = true;

			//Store the Ice Block because we will need its fire direction later
			if (const auto storage = m_pActor->GetComponent<GameObjectStorage>())
				storage->StoreGameObject(other);
		}
	}
}

//Change Direction -> Can be placed in the DirectionComponent
void SnowBeeState::ChangeMovement()
{
	m_pActor->GetComponent<MoveComponent>()->ResetMovement();
	if (const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator
		const glm::vec2 oldDirection{ directionComponent->GetDirection() };

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
