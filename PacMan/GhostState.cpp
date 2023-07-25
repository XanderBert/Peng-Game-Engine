#include "GhostState.h"

#include <iostream>

#include "CountdownComponent.h"
#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "GhostComponent.h"
#include "MoveComponent.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "PacDotComponent.h"
#include "WallComponent.h"
#include "IntersectionComponent.h"
#include "TriggerComponent.h"

ChaseState::ChaseState(GameObject* object) : State(object)
{
	OnEnter();
}

State* ChaseState::HandleInput()
{
	return nullptr;
}

void ChaseState::Update()
{
	// Move
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

	const auto worldPos = m_pActor->GetComponent<Transform>()->GetWorldPosition();


	StorePacMan();
	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();

	// Reset the ghost's direction towards the new target position
	//m_pActor->GetComponent<DirectionComponent>()->SetDirection(CalculateDirection());
}

void ChaseState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//The Ghost  is colliding with a Intersection Trigger
	if(other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		if(glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint()) >= 2.f) return;

		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();
		const auto desiredDirection = CalculateDirection();


		const auto directionComponent = m_pActor->GetComponent<DirectionComponent>();

		//Go over every possible direction. 
		for (const auto& direction : possibleDirections)
		{
			// If the desired direction is available, set that direction
			if (direction == desiredDirection)
			{
				directionComponent->SetDirection(desiredDirection);
				return;
			}
		}

		// If the desired direction is not available, choose another direction
		const std::vector<glm::vec2> desiredDirections{ {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
		for (const auto& desiredDir : desiredDirections)
		{
			// Calculate the dot product between the desired direction and the current direction
			const float dotProduct = glm::dot(desiredDir, directionComponent->GetDirection());

			// If the dot product is -1, it's a 180-degree turn, so skip it
			if (glm::abs(dotProduct + 1.0f) < std::numeric_limits<float>::epsilon())
			{
				continue;
			}

			// Check if the alternative direction is available
			for (const auto& direction : possibleDirections)
			{
				if (direction == desiredDir)
				{
					directionComponent->SetDirection(desiredDir);
					return;
				}
			}
		}

		// If no valid direction is found, you can handle it here (e.g., pick a random direction).
		// For example:
		// directionComponent->SetDirection(possibleDirections[0]);


	}


	//The Ghost Trigger is colliding with a wall
	if(other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		
	}
}

void ChaseState::OnEnter()
{
	m_pActor->GetComponent<CountdownComponent>()->SetTime(1.0f);
	m_pActor->GetComponent<CountdownComponent>()->Play();

	StorePacMan();
	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
	m_pActor->GetComponent<DirectionComponent>()->SetDirection(CalculateDirection());
}

glm::vec2 ChaseState::CalculateDirection() const
{
	const auto worldPos = m_pActor->GetComponent<Transform>()->GetWorldPosition();
	const auto vector = m_Target - worldPos;

	if (glm::abs(vector.x) > glm::abs(vector.y))
	{
		if (vector.x > 0)
		{
			return	{ 1,0 };
		}

		return	{- 1,0 };
		
	}
	
	if (vector.y > 0)
	{
		return{ 0,1 };
	}

	return { 0,-1 };
}

void ChaseState::StorePacMan()
{
	//--
	//Find pac Man
	//--

	const auto storage = m_pActor->GetComponent<GameObjectStorage>();
	if (storage->GetStoredObject() == nullptr || storage->GetStoredObject()->GetComponent<PacManComponent>() == nullptr)
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

		if (storage->GetStoredObject()->GetComponent<PacManComponent>() == nullptr)
		{
			assert(false && "Pacman not found");
		}
	}
}














ScatterState::ScatterState(GameObject* object) : State(object)
{
	OnEnter();
}

State* ScatterState::HandleInput()
{
	return nullptr;
}

void ScatterState::Update()
{
}

void ScatterState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
}

void ScatterState::OnEnter()
{
}












FrightenedState::FrightenedState(GameObject* object) : State(object)
{
	OnEnter();
}

State* FrightenedState::HandleInput()
{
	return nullptr;
}

void FrightenedState::Update()
{
}

void FrightenedState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
}

void FrightenedState::OnEnter()
{
}