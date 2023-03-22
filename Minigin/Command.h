#pragma once
#include "GameActor.h"
class GameActor;

class Command
{
public:
	explicit Command(GameActor* pActor);
	virtual ~Command();

	Command(const Command& other) = delete;
	Command(Command&& other)noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other)noexcept = delete;

	virtual void Execute() = 0;
protected:
	GameActor* GetActor() const { return m_pActor; }
private:
	GameActor* m_pActor{ nullptr };
};

class JumpCommand : public Command
{
public:
	void Execute() override { GetActor()->Jump(); }

};

class MoveCommand : public Command
{
public:
	void Execute() override { GetActor()->Move(glm::vec2{}); }

};
