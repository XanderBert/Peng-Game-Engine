#include "GhostState.h"

#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "MoveComponent.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"

GhostMoveState::GhostMoveState(GameObject* object) : State(object)
{
	OnEnter();
}

State* GhostMoveState::HandleInput()
{
	return nullptr;
}

void GhostMoveState::Update()
{
	const auto storage = m_pActor->GetComponent<GameObjectStorage>();

	//If Pacman is not valid
	if(storage->GetStoredObject() == nullptr || storage->GetStoredObject()->GetComponent<PacManComponent>() == nullptr)
	{
		//Get All objects in the scene
		const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
		
		//Find the object with the pacman component and store it in the ghost
		for (const auto& object : objects)
		{
			if (object->GetComponent<PacManComponent>())
			{
				storage->StoreGameObject(object);
			}
		}

		if(storage->GetStoredObject()->GetComponent<PacManComponent>() == nullptr)
		{
			assert(false && "Pacman not found");
		}
	}

	const auto pacMan = storage->GetStoredObject();
	const auto pacManLocation = pacMan->GetComponent<Transform>()->GetWorldPosition();
	const auto vector = pacManLocation - m_pActor->GetComponent<Transform>()->GetWorldPosition();

	if(glm::abs(vector.x) > glm::abs(vector.y))
	{
		if(vector.x > 0)
		{
			m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 1,0 });
		}
		else
		{
			m_pActor->GetComponent<DirectionComponent>()->SetDirection({ -1,0 });
		}
	}
	else
	{
		if (vector.y > 0)
		{
			m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 0,1 });
		}
		else
		{
			m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 0,-1 });
		}
	}


	//Find towards wich direction pacman is located. Try to move in that direction.
	//Collide? Try to move in another direction.
	//Collide again? find in wich directio pacman is and try to move towards that direction.
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

}

void GhostMoveState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	m_pActor->GetComponent<MoveComponent>()->ResetMovement();

	if (const auto directionComponent = m_pActor->GetComponent<DirectionComponent>())
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr) + std::rand()));


		// Seed the random number generator
		const glm::vec2 oldDirection{ directionComponent->GetDirection() };

		auto newDirection = oldDirection;


		// Generate a new direction until it is different from the old direction
		while (newDirection == oldDirection)
		{
			// Generate a random integer between 0 and 3
			const int numQuarterTurns = std::rand() % 4;
			
			// Perform the quarter turns
			for (int i = 0; i < numQuarterTurns; ++i)
			{
				const float temp = newDirection.x;
				newDirection.x = -newDirection.y;
				newDirection.y = temp;
			}
		}

		directionComponent->SetDirection(newDirection);
	}
}

void GhostMoveState::OnEnter()
{
	
}

















GhostConcusedState::GhostConcusedState(GameObject* object) : State(object)
{
	OnEnter();
}

State* GhostConcusedState::HandleInput()
{
	return nullptr;
}

void GhostConcusedState::Update()
{
}

void GhostConcusedState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
}

void GhostConcusedState::OnEnter()
{
}
