#include "GhostState.h"
#include "CountdownComponent.h"
#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "GhostComponent.h"
#include "MoveComponent.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "Transform.h"
#include "WallComponent.h"
#include "IntersectionComponent.h"
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


	if (!m_pActor->GetComponent<GhostComponent>()->IsCornering())
	{
		//Store Pacman in the storage component if needed.
		m_pActor->GetComponent<GhostComponent>()->StorePacMan();

		//Set pacman As the target
		const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();
		m_Target = pacMan->GetComponent<Transform>()->GetWorldPosition();
		m_pActor->GetComponent<GhostComponent>()->SetTarget(m_Target);
		return;
	}


	const auto distance = glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), m_Target);
	if (distance <= 0.5f && m_pActor->GetComponent<GhostComponent>()->IsCornering())
	{
		m_pActor->GetComponent<DirectionComponent>()->SetDirection(m_NewDirection);
		m_pActor->GetComponent<GhostComponent>()->SetCornering(false);
	}

	m_pActor->GetComponent<GhostComponent>()->SetTarget(m_Target);
}

void ChaseState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::PacManDied, other);
		return;
	}

	if (other->GetComponent<IntersectionComponent>())
	{
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();
		return;
	}

	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void ChaseState::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//The Ghost  is colliding with a Intersection Trigger
	if (other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		//Move the ghost a bit forward, Then let it turn
		const auto transform = m_pActor->GetComponent<Transform>();
		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();

		m_NewDirection = m_pActor->GetComponent<GhostComponent>()->GetDirectionOfVector(possibleDirections, m_Target);
		if (m_NewDirection == m_pActor->GetComponent<DirectionComponent>()->GetDirection()) { return; }

		m_pActor->GetComponent<GhostComponent>()->SetCornering(true);
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();

		m_pActor->GetComponent<GhostComponent>()->CenterGhost(m_Target, m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint());
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
	// Move
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

	const auto distance = glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), m_Target);
	if (distance <= 0.5f && m_pActor->GetComponent<GhostComponent>()->IsCornering())
	{
		m_pActor->GetComponent<DirectionComponent>()->SetDirection(m_NewDirection);
		m_pActor->GetComponent<GhostComponent>()->SetCornering(false);
	}

	m_pActor->GetComponent<GhostComponent>()->SetTarget(m_Target);
}

void ScatterState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::PacManDied, other);
		return;
	}

	if (other->GetComponent<IntersectionComponent>())
	{
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();
		return;
	}

	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void ScatterState::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//The Ghost  is colliding with a Intersection Trigger
	if (other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		//Move the ghost a bit forward, Then let it turn
		const auto transform = m_pActor->GetComponent<Transform>();
		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();

		m_NewDirection = m_pActor->GetComponent<GhostComponent>()->GetRandomPossibleDirection(possibleDirections);
		if (m_NewDirection == m_pActor->GetComponent<DirectionComponent>()->GetDirection()) { return; }

		m_pActor->GetComponent<GhostComponent>()->SetCornering(true);
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();

		m_pActor->GetComponent<GhostComponent>()->CenterGhost(m_Target, m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint());
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
		return m_pActor->GetComponent<GhostComponent>()->GetRandomPossibleState();
	}

	return nullptr;
}

void FrightenedState::Update()
{
	// Move
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

	const auto distance = glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), m_Target);
	if (distance <= 0.5f && m_pActor->GetComponent<GhostComponent>()->IsCornering())
	{
		m_pActor->GetComponent<DirectionComponent>()->SetDirection(m_NewDirection);
		m_pActor->GetComponent<GhostComponent>()->SetCornering(false);
	}

	m_pActor->GetComponent<GhostComponent>()->SetTarget(m_Target);
}

void FrightenedState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with PacMan
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{

		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::GhostEaten, m_pActor);

		return;
	}

	if (other->GetComponent<IntersectionComponent>())
	{
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();
		return;
	}

	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void FrightenedState::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//The Ghost  is colliding with a Intersection Trigger
	if (other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		//Move the ghost a bit forward, Then let it turn
		const auto transform = m_pActor->GetComponent<Transform>();
		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();

		m_NewDirection = m_pActor->GetComponent<GhostComponent>()->GetRandomPossibleDirection(possibleDirections);
		if (m_NewDirection == m_pActor->GetComponent<DirectionComponent>()->GetDirection()) { return; }

		m_pActor->GetComponent<GhostComponent>()->SetCornering(true);
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();

		m_pActor->GetComponent<GhostComponent>()->CenterGhost(m_Target, m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint());
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


	if (!m_pActor->GetComponent<GhostComponent>()->IsCornering())
	{
		//Store Pacman in the storage component if needed.
		m_pActor->GetComponent<GhostComponent>()->StorePacMan();

		//Set pacman As the target
		//Get Pacman
		const auto pacMan = m_pActor->GetComponent<GameObjectStorage>()->GetStoredObject();

		//Try to figure out where pacman is going.
		const auto pacManDirection = pacMan->GetComponent<DirectionComponent>()->GetDirection();
		const auto pacManVelocity = pacMan->GetComponent<VelocityComponent>()->GetVelocity();
		constexpr float timeModifier = 13.f;
		const auto pacManExpectedPosition = pacMan->GetComponent<Transform>()->GetWorldPosition() + (pacManDirection * pacManVelocity * timeModifier * TimeM::GetInstance().GetDeltaTimeM());
		m_Target = pacManExpectedPosition;

		m_pActor->GetComponent<GhostComponent>()->SetTarget(m_Target);
		return;
	}

	const auto distance = glm::distance(m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint(), m_Target);
	if (distance <= 0.5f && m_pActor->GetComponent<GhostComponent>()->IsCornering())
	{
		m_pActor->GetComponent<DirectionComponent>()->SetDirection(m_NewDirection);
		m_pActor->GetComponent<GhostComponent>()->SetCornering(false);
	}

	m_pActor->GetComponent<GhostComponent>()->SetTarget(m_Target);


}

void CorneringState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//Colliding with a ghost
	if (other->GetComponent<PacManComponent>() && !isSenderTrigger && !isTrigger)
	{
		other->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::PacManDied, other);
		return;
	}

	if (other->GetComponent<IntersectionComponent>())
	{
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();
		return;
	}

	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
		return;
	}
}

void CorneringState::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	//The Ghost  is colliding with a Intersection Trigger
	if (other->GetComponent<IntersectionComponent>() && isTrigger && !isSenderTrigger)
	{
		//If the ghost is not in the center of the intersection -> return
		//Move the ghost a bit forward, Then let it turn
		const auto transform = m_pActor->GetComponent<Transform>();
		const auto possibleDirections = other->GetComponent<IntersectionComponent>()->GetDirections();

		m_NewDirection = m_pActor->GetComponent<GhostComponent>()->GetDirectionOfVector(possibleDirections, m_Target);
		if (m_NewDirection == m_pActor->GetComponent<DirectionComponent>()->GetDirection()) { return; }

		m_pActor->GetComponent<GhostComponent>()->SetCornering(true);
		m_Target = other->GetComponent<TriggerComponent>()->GetColliderMiddlePoint();

		m_pActor->GetComponent<GhostComponent>()->CenterGhost(m_Target, m_pActor->GetComponent<BoxCollider>()->GetColliderMiddlePoint());
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
















IdleState::IdleState(GameObject* object) : State(object)
{
	OnEnter();
}

State* IdleState::HandleInput()
{
	if (m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
	{
		const auto ghostComponent = m_pActor->GetComponent<GhostComponent>();
		const auto ghostStartingPosition = ghostComponent->GetStartPosition();

		m_pActor->GetComponent<Transform>()->SetWorldPosition(ghostStartingPosition);
		m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 0,-1 });
		return m_pActor->GetComponent<GhostComponent>()->GetRandomPossibleState();
	}

	return nullptr;
}

void IdleState::Update()
{
	//Move the ghost up and down in the center of the map.

	//Move
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);
}

void IdleState::OnCollision(GameObject* other, bool /*isTrigger*/, bool isSenderTrigger)
{
	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();


		//Inverse Direction
		const auto& directionComp = m_pActor->GetComponent<DirectionComponent>();
		const auto& direction = directionComp->GetDirection();
		directionComp->SetDirection(-direction);
		return;
	}
}

void IdleState::OnEnter()
{
	m_pActor->GetComponent<VelocityComponent>()->SetVelocityPercentage(50.f);

	//Store Pacman in the storage component if needed.
	const auto ghostComponent = m_pActor->GetComponent<GhostComponent>();
	ghostComponent->StorePacMan();

	//Start the countdown to go out of the idle state.
	//Setup the timer for the ghost to go out of the idle state

	const auto countDownComponent = m_pActor->GetComponent<CountdownComponent>();
	countDownComponent->Pause();
	countDownComponent->SetTime(4.5f * static_cast<float>(ghostComponent->GetGhostNumber()));
	countDownComponent->Play();

	m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 0,-1 });
}










WasEatenState::WasEatenState(GameObject* object) : State(object)
{
	OnEnter();

}

State* WasEatenState::HandleInput()
{
	if (glm::distance(m_pActor->GetComponent<Transform>()->GetWorldPosition(), m_pActor->GetComponent<GhostComponent>()->GetStartPosition()) < 0.5f)
	{
		m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 0,-1 });

		return m_pActor->GetComponent<GhostComponent>()->GetRandomPossibleState();
	}

	return nullptr;
}

void WasEatenState::Update()
{
	m_pActor->GetComponent<MoveComponent>()->SetCanMove(true);

	const auto ghostComp = m_pActor->GetComponent<GhostComponent>();
	const auto direction = ghostComp->GetDirectionOfVector({ {1,0}, {-1,0}, {0,1}, {0,-1} }, ghostComp->GetStartPosition());

	m_pActor->GetComponent<DirectionComponent>()->SetDirection(direction);
}

void WasEatenState::OnEnter()
{
	m_pActor->GetComponent<VelocityComponent>()->SetVelocityPercentage(100.f);
	const auto ghostComp = m_pActor->GetComponent<GhostComponent>();

	ghostComp->SetTarget(ghostComp->GetStartPosition());

	//Change the sprite to the eyes
}
