#pragma once
#include <memory>
#include <unordered_map>
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
	virtual std::vector<Controller*> GetUsedControllers() = 0;
	virtual std::vector<Controller*> GetControllers() = 0;

	virtual bool GetButtonPressed(SDL_KeyCode) const = 0;
	virtual bool GetButtonPressed(int controllerId, Controller::ControllerButton controllerButton) const = 0;
	virtual Controller* GetController(int controllerId) const = 0;

	virtual void RegisterCommand(SDL_Keycode key, Controller::ControllerButton controllerButton, Command* command) = 0;
	virtual void HandleInput(Controller::ControllerButton key) = 0;
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

	bool ProcessInput() override;
	std::vector<Controller*> GetUsedControllers() override;
	std::vector<Controller*> GetControllers() override;
	bool GetButtonPressed(SDL_KeyCode key) const override;
	bool GetButtonPressed(int controllerId, Controller::ControllerButton controllerButton) const override;
	Controller* GetController(int controllerId) const override { return m_pControllers[controllerId].get(); }


	void RegisterCommand(SDL_Keycode key, Controller::ControllerButton controllerButton, Command* command) override;
	void HandleInput(Controller::ControllerButton key) override;

private:
	std::unordered_map<SDL_Keycode, std::unique_ptr<Command>> m_KeyboardCommands{};

	//std::unordered_map<Controller::ControllerButton, std::unique_ptr<Command>> m_ControllerCommands{};

	std::vector<std::unique_ptr<Controller>> m_pControllers{};
	SDL_Keycode m_Input{};

	void CheckIfControllerNeedsToBeAdded();
};