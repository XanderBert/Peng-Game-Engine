#pragma once
#include "Command.h"
#include "GameObject.h"
#include "LevelLoader.h"

class SkipLevelCommand final : public Command
{
public:
	SkipLevelCommand(InputType type) : Command(type) {}
	~SkipLevelCommand() override = default;

	void Execute() override
	{
		LevelLoader::GetInstance().LoadNextLevel();
	}

};

