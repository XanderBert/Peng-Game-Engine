#pragma once
#include <glm/vec2.hpp>
#include "Command.h"
#include "TimeM.h"
#include "Transform.h"
#include "GameActor.h"

class MoveCommand final : public Command
{
public:
	MoveCommand(GameActor* gameActor, const glm::vec2 movmentDirection)
		: m_GameActor(gameActor)
		, m_MovementDirection(movmentDirection)
	{}

	virtual ~MoveCommand() override = default;

	void Execute() override
	{
		m_GameActor->SetDirection(m_MovementDirection);

		const auto transform = m_GameActor->GetComponent<Transform>();
		const auto movement{ m_MovementDirection * m_GameActor->GetVelocity() * TimeM::GetInstance().GetDeltaTimeM() };

		transform->SetWorldPosition(transform->GetWorldPosition() + movement);
	}
private:
	GameActor* m_GameActor;
	glm::vec2 m_MovementDirection;
};

