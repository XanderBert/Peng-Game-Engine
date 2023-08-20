#pragma once
#include <glm/vec2.hpp>
#include "Command.h"
#include "DirectionComponent.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MoveComponent.h"
#include "TimeM.h"
#include "VelocityComponent.h"



//Save the last direction.
//Check if a collision will happen.
//If so don't change direction
//when no collision will happen change direction



//How do i keep checking if a collision will happen?

//In the state update.

class MoveCommand final : public Command
{
public:
	MoveCommand(GameObject* gameActor, const glm::vec2 movementDirection, InputType type)
		: Command(type)
		, m_GameActor(gameActor)
		, m_MovementDirection(movementDirection)
	{}

	~MoveCommand() override = default;

	void Execute() override
	{

		const auto velocity = m_GameActor->GetComponent<VelocityComponent>();


		if (const auto spriteRenderer{ m_GameActor->GetComponent<SpriteRenderer>() })
		{
			if (spriteRenderer->GetOffset() == glm::vec2{ 0,16 }) return;
		}


		if (const auto directionComponent{ m_GameActor->GetComponent<DirectionComponent>() })
		{
			directionComponent->SetDirection(m_MovementDirection);
		}


		m_GameActor->GetComponent<MoveComponent>()->SetCanMove(true);
	}
private:
	GameObject* m_GameActor;
	glm::vec2 m_MovementDirection;
};
