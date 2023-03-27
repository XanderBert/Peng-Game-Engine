#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.h"
#include "Controller.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Singleton.h"


class InputManager final : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager() override;
	bool ProcessInput();
	void AddActor(GameActor* actor) { m_pActors.push_back(actor); }
	std::vector<Controller*> GetUsedControllers();
	std::vector<Controller*> GetControllers();
private:

	////using ControllerKey = 
	//using ControllerCommandsMap = std::map< std::pair<unsigned, Controller::ControllerButton>, std::unique_ptr<Command>>;
	//ControllerCommandsMap m_consoleCommands{};

	Command* m_pButtonX{};
	Command* m_pButtonY{};
	Command* m_pButtonA{};
	Command* m_pButtonB{};
	Command* m_pLeftThumbStick{};
	std::vector<std::unique_ptr<Controller>> m_pControllers{};

	std::vector<GameActor*> m_pActors{};

	void CheckIfControllerNeedsToBeAdded();
};