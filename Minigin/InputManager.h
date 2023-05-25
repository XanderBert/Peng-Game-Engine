#pragma once
#include <memory>
#include <vector>
#include "Command.h"
#include "Controller.h"
#include "SDL.h"

class null_InputManager
{
public:
	null_InputManager() = default;
	virtual ~null_InputManager() = default;

	null_InputManager(const null_InputManager& other) = delete;
	null_InputManager(null_InputManager&& other)noexcept = delete;
	null_InputManager& operator=(const null_InputManager& other) = delete;
	null_InputManager& operator=(null_InputManager&& other)noexcept = delete;

	virtual bool ProcessInput() = 0;
	virtual void AddActor(GameActor*) = 0;
	virtual std::vector<Controller*> GetUsedControllers() = 0;
	virtual std::vector<Controller*> GetControllers() = 0;

	virtual bool GetButtonPressed(SDL_KeyCode) const = 0;
	virtual bool GetButtonPressed(int controllerId, Controller::ControllerButton controllerButton) const = 0;
	virtual Controller* GetController(int controllerId) const = 0;
};


class InputManager final : public null_InputManager
{
public:
	InputManager();
	virtual ~InputManager() override;

	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other)noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other)noexcept = delete;

	virtual bool ProcessInput() override;
	virtual void AddActor(GameActor* actor) override { m_pActors.push_back(actor); }
	virtual std::vector<Controller*> GetUsedControllers() override;
	virtual std::vector<Controller*> GetControllers() override;
	virtual bool GetButtonPressed(SDL_KeyCode key) const override;
	virtual bool GetButtonPressed(int controllerId, Controller::ControllerButton controllerButton) const override;
	virtual Controller* GetController(int controllerId) const override { return m_pControllers[controllerId].get(); }

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

	SDL_Keycode m_Input{};

	void CheckIfControllerNeedsToBeAdded();
};