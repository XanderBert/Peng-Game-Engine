#pragma once
#include "Command.h"
#include <ServiceLocator.h>


class MuteCommand final : public Command
{
public:
	MuteCommand(InputType type)
		: Command(type) {}

	~MuteCommand() override = default;

	void Execute() override
	{
		auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
		audioService.ToggleMute();
	}
};
