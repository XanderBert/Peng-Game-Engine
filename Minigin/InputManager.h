#pragma once
#include <memory>
#include <vector>
#include "Command.h"
#include "Controller.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other)noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other)noexcept = delete;

	virtual bool ProcessInput();
	virtual void AddActor(GameActor* actor) { m_pActors.push_back(actor); }
	virtual std::vector<Controller*> GetUsedControllers();
	virtual std::vector<Controller*> GetControllers();
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

class null_InputManager final : public InputManager
{
public:
	bool ProcessInput() override { return false; }
	void AddActor([[maybe_unused]] GameActor* actor) override {}
	std::vector<Controller*> GetUsedControllers() override { return std::vector<Controller*> {}; }
	std::vector<Controller*> GetControllers() override { return std::vector<Controller*> {}; }
};