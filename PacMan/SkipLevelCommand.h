#pragma once
#include "Command.h"
#include "GameObject.h"
#include "LevelLoader.h"

class SkipLevelCommand final : public Command
{
public:
	SkipLevelCommand() {}
	~SkipLevelCommand() override = default;

	void Execute() override
	{
		LevelLoader::GetInstance().LoadNextLevel();
	}

};

