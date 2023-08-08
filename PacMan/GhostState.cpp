#include "GhostState.h"
#include "CountdownComponent.h"
#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "GhostComponent.h"
#include "MoveComponent.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "WallComponent.h"
#include "IntersectionComponent.h"
#include "StateComponent.h"
#include "TriggerComponent.h"
#include "VelocityComponent.h"

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


	//Store Pacman in the storage component if needed.
	StorePacMan();

	//Set pacman As the target
	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
}

void ChaseState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->Die();
		return;
	}


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
				// Calculate the dot product between the desired direction and the current direction
				const float dotProduct = glm::dot(desiredDirection, directionComponent->GetDirection());

				// If the dot product is -1, it's a 180-degree turn, so skip it
				if (glm::abs(dotProduct + 1.0f) < std::numeric_limits<float>::epsilon())
				{
					continue;
				}


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
		// If no valid direction is found
		// directionComponent->SetDirection(possibleDirections[0]);
	}


	//The Ghost Trigger is colliding with a wall
	if(other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void ChaseState::OnEnter()
{
	m_pActor->GetComponent<GhostComponent>()->InitChaseAndScatterSprites();
	m_pActor->GetComponent<CountdownComponent>()->Play();
	m_pActor->GetComponent<VelocityComponent>()->SetVelocityPercentage(95.f);



	StorePacMan();
	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
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
	if (m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
	{
		return new ChaseState(m_pActor);
	}

	return nullptr;
}

void ScatterState::Update()
{
	//Make a ghost component for every ghost. make different cases for it?

	//if(m_pActor->GetComponent<GhostComponent>()->GetTexturePath() == "GhostBlue.png")
	//{
	//	
	//}
}

void ScatterState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->Die();
		return;
	}

	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void ScatterState::OnEnter()
{
	m_pActor->GetComponent<GhostComponent>()->InitChaseAndScatterSprites();

	const auto countDownComponent = m_pActor->GetComponent<CountdownComponent>();
	countDownComponent->SetTime(20.f);
	countDownComponent->ResetTime();
	m_pActor->GetComponent<VelocityComponent>()->SetVelocityPercentage(50.f);
}












FrightenedState::FrightenedState(GameObject* object) : State(object)
{
	OnEnter();
}

State* FrightenedState::HandleInput()
{
	if(m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
	{
		return new ChaseState(m_pActor);
	}

	return nullptr;
}

void FrightenedState::Update()
{
	// Move
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);
	m_directionChangeTime += TimeM::GetInstance().GetDeltaTimeM();
}

void FrightenedState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<Transform>()->SetWorldPosition({ 68,90 });
		m_pActor->GetComponent<StateComponent>()->SetState(new ChaseState(m_pActor));
		return;
	}

	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
	
	if (other->GetComponent<IntersectionComponent>() != nullptr)
	{
		//If the ghost is not in the center of the intersection -> return
		if (glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint()) >= 2.f) return;

		const auto intersection = other->GetComponent<IntersectionComponent>();

		if (isTrigger && !isSenderTrigger)
		{
			const auto directionComponent = m_pActor->GetComponent<DirectionComponent>();
			auto number = 0;

			while (glm::abs(directionComponent->GetDirection()) == glm::abs(intersection->GetDirections()[number]))
			{
				number = std::rand() % intersection->GetDirections().size();
			}
			
			// Check if the direction is changing
			if (directionComponent->GetDirection() != m_previousDirection) 
			{
				m_wasDirectionChanged = true;
				m_directionChangeTime = 0.0f;
				m_previousDirection = directionComponent->GetDirection();
			}

			if (m_wasDirectionChanged && m_directionChangeTime < 0.1f) 
			{
				
				directionComponent->SetDirection(m_previousDirection);
			}
			else 
			{
				m_wasDirectionChanged = false;
				directionComponent->SetDirection(intersection->GetDirections().at(number));
			}
		}

		return;
	}
}

void FrightenedState::OnEnter()
{

	const auto countDownComponent = m_pActor->GetComponent<CountdownComponent>();
	countDownComponent->SetTime(5.f);
	countDownComponent->ResetTime();

	m_pActor->GetComponent<GhostComponent>()->InitScaredSprites();
	m_pActor->GetComponent<VelocityComponent>()->SetVelocityPercentage(60.f);
}