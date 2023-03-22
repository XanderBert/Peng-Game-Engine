#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.h"
#include "Controller.h"
#include "Singleton.h"


class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();

private:
	std::unique_ptr<Command> buttonX;


	//using ControllerKey = 
	using ControllerCommandsMap = std::map< std::pair<unsigned, Controller::ControllerButton>, std::unique_ptr<Command>>;
	ControllerCommandsMap m_consoleCommands{};

	std::vector<std::unique_ptr<Controller>> m_Controllers{};
};
