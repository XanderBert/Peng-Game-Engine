#pragma once
#include <glm/vec2.hpp>
#include "Command.h"
#include "DirectionComponent.h"
#include "TimeM.h"
#include "Transform.h"
#include "PengoEvents.h"
#include "VelocityComponent.h"

class MoveCommand final : public Command
{
public:
	MoveCommand(GameObject* gameActor, const glm::vec2 movementDirection)
		: m_GameActor(gameActor)
		, m_MovementDirection(movementDirection)
	{}

	virtual ~MoveCommand() override = default;

	void Execute() override
	{
		if (const auto directionComponent{ m_GameActor->GetComponent<DirectionComponent>() })
		{
			directionComponent->SetDirection(m_MovementDirection);
		}

		const auto transform = m_GameActor->GetComponent<Transform>();
		const auto velocity = m_GameActor->GetComponent<VelocityComponent>();
		const auto movement{ m_MovementDirection * velocity->GetVelocity() * TimeM::GetInstance().GetDeltaTimeM() };

		transform->SetWorldPosition(transform->GetWorldPosition() + movement);
	}
private:
	GameObject* m_GameActor;
	glm::vec2 m_MovementDirection;
};

