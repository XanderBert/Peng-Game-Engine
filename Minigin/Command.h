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

	//Todo: There will be commands that don't need game actors or other params
	//virtual void Execute(const glm::vec2& value) = 0;
	//virtual void Execute() = 0;
};

class AttackCommand final : public Command
{
public:
	void Execute(GameActor& actor, [[maybe_unused]] const glm::vec2& value) override
	{
		actor.Attack();
	}
};

class MoveCommand final : public Command
{
public:
	void Execute(GameActor& actor, const glm::vec2& value) override
	{
		actor.Move(value);
	}

};
