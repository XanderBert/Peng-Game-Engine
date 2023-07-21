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

	//--
	//Find pac Man
	//--

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


		m_pActor->GetComponent<CountdownComponent>()->ResetTime();
	}


	//Get the location of pacman and the ghost
	const auto pacMan = storage->GetStoredObject();
	const auto pacManLocation = pacMan->GetComponent<Transform>()->GetWorldPosition();
	const auto vector = pacManLocation - m_pActor->GetComponent<Transform>()->GetWorldPosition();


	if(m_pActor->GetComponent<CountdownComponent>()->GetTime() < 0.f) 
	{
		m_pActor->GetComponent<CountdownComponent>()->ResetTime();

		//Set the Direction
		if (glm::abs(vector.x) > glm::abs(vector.y))
		{
			if (vector.x > 0)
			{
				m_pActor->GetComponent<GhostComponent>()->ChangeDirection({ 1,0 });
			}
			else
			{
				m_pActor->GetComponent<GhostComponent>()->ChangeDirection({ -1,0 });
			}
		}
		else
		{
			if (vector.y > 0)
			{
				m_pActor->GetComponent<GhostComponent>()->ChangeDirection({ 0,1 });
			}
			else
			{
				m_pActor->GetComponent<GhostComponent>()->ChangeDirection({ 0,-1 });
			}
		}		
	}
	
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

}

void GhostMoveState::OnCollision(GameObject* other, bool /*isTrigger*/, bool isSenderTrigger)
{
	//The Ghost Trigger is colliding with a wall
	if(other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		m_pActor->GetComponent<GhostComponent>()->ChangeToRandomDirection();
	}
}

void GhostMoveState::OnEnter()
{
	m_pActor->GetComponent<CountdownComponent>()->SetTime(1.0f);
	m_pActor->GetComponent<CountdownComponent>()->Play();
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

void GhostConcusedState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
}

void GhostConcusedState::OnEnter()
{
}
