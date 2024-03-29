#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
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
	virtual std::vector<Controller*> GetControllers() = 0;

	virtual bool GetButtonDown(SDL_Keycode) const = 0;
	virtual bool GetButtonDown(int controllerId, Controller::ControllerButton controllerButton) const = 0;

	virtual bool GetButtonPressed(SDL_Keycode key) const = 0;

	virtual bool IsLeftMouseButtonPressed() const = 0;
	virtual glm::vec2 GetLeftMouseButtonPressed() const = 0;

	virtual Controller* GetController(int controllerId) const = 0;
	virtual Controller* AddController(int controllerIndex) = 0;
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
	std::vector<Controller*> GetControllers() override;

	bool GetButtonDown(SDL_Keycode key) const override;
	bool GetButtonDown(int controllerId, Controller::ControllerButton controllerButton) const override;

	bool GetButtonPressed(SDL_Keycode key) const override;

	bool IsLeftMouseButtonPressed() const override;
	glm::vec2 GetLeftMouseButtonPressed() const override;

	Controller* GetController(int controllerId) const override { return m_pControllers[controllerId].get(); }
	Controller* AddController(int controllerIndex) override;



private:
	std::vector<std::unique_ptr<Controller>> m_pControllers{};
	std::unordered_map<SDL_Keycode, bool> m_KeyStates;
	SDL_Keycode m_Input{};
	void UpdateControllersInput() const;
	bool UpdateKeyboardInput();
};