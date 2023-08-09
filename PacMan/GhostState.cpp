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
#include "TimeM.h"
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
	m_pActor->GetComponent<GhostComponent>()->StorePacMan();

	//Set pacman As the target
	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
}

void ChaseState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::PacManDied, other);
		return;
	}


	//The Ghost  is colliding with a Intersection Trigger
	if (other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		if (glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint()) >= 2.f) return;
		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();
		m_pActor->GetComponent<DirectionComponent>()->SetDirection(m_pActor->GetComponent<GhostComponent>()->GetDirectionOfVector(possibleDirections, m_Target));
	}


	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && isSenderTrigger)
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

	//Store Pacman in the storage component if needed.
	m_pActor->GetComponent<GhostComponent>()->StorePacMan();

	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
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
		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::PacManDied, m_pActor);
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
	if (m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
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
	//Colliding with PacMan
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{

		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::GhostEaten, m_pActor);

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







CorneringState::CorneringState(GameObject* object) : State(object)
{
	OnEnter();
}

State* CorneringState::HandleInput()
{
	return nullptr;
}

void CorneringState::Update()
{
	// Move
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

	//Store Pacman in the storage component if needed.
	m_pActor->GetComponent<GhostComponent>()->StorePacMan();

	//Get Pacman
	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();

	//Try to figure out where pacman is going.
	const auto pacManDirection = pacMan->GetComponent<DirectionComponent>()->GetDirection();
	const auto pacManVelocity = pacMan->GetComponent<VelocityComponent>()->GetVelocity();
	constexpr float timeModifier = 1.5f;
	const auto pacManExpectedPosition = pacMan->GetComponent<Transform>()->GetWorldPosition() + (pacManDirection * pacManVelocity * timeModifier);
	m_Target = pacManExpectedPosition;
}

void CorneringState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::PacManDied, other);
		return;
	}


	//The Ghost  is colliding with a Intersection Trigger
	if (other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		if (glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint()) >= 2.f) return;

		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();
		const auto newDirection = m_pActor->GetComponent<GhostComponent>()->GetDirectionOfVector(possibleDirections, m_Target);

		m_pActor->GetComponent<DirectionComponent>()->SetDirection(newDirection);
	}


	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void CorneringState::OnEnter()
{

	m_pActor->GetComponent<GhostComponent>()->InitChaseAndScatterSprites();
	m_pActor->GetComponent<CountdownComponent>()->Play();
	m_pActor->GetComponent<VelocityComponent>()->SetVelocityPercentage(95.f);

	//Store Pacman in the storage component if needed.
	m_pActor->GetComponent<GhostComponent>()->StorePacMan();

	const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
	m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
}
