#pragma once
#include <iostream>

#include "GameActor.h"
class GameActor;

class Command
{
public:
	explicit Command() = default;
	virtual ~Command();

	Command(const Command& other) = delete;
	Command(Command&& other)noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other)noexcept = delete;

	virtual void Execute(GameActor& actor, const glm::vec2& value) = 0;
};

class JumpCommand : public Command
{
public:
	void Execute(GameActor& actor, [[maybe_unused]] const glm::vec2& value) override
	{
		actor.Jump();
	}
};

class MoveCommand : public Command
{
public:
	void Execute(GameActor& actor, const glm::vec2& value) override
	{
		actor.Move(value);
	}

};
