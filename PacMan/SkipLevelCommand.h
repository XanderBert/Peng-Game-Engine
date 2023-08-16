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
		std::cout << "NExt LEvell\n";


		LevelLoader::GetInstance().LoadLevel(LevelLoader::GetInstance().GetLevelId() + 1);
	}

};

