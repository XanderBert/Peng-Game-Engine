#pragma once
#include "Command.h"
#include "Component.h"
#include "Controller.h"
#include "InputManager.h"


class ControllerComponent final : public Component
{
public:
	ControllerComponent(GameObject* owner);
	virtual  ~ControllerComponent() override;

	ControllerComponent(const ControllerComponent& other) = delete;
	ControllerComponent(ControllerComponent&& other) noexcept = delete;
	ControllerComponent& operator=(const ControllerComponent& other) = delete;
	ControllerComponent& operator=(ControllerComponent&& other) = delete;

	virtual void Update() override;
	virtual void FixedUpdate(float /*fixedTimeMStep*/) override {}
	virtual void LateUpdate() override {}
	virtual void Render() override {}

	void AddBinding(Controller::ControllerButton button, Command* command);
	std::unordered_map<Controller::ControllerButton, Command*>& GetControllerCommands() { return m_ControllerCommands; }

	template <typename T>
	std::vector<Controller::ControllerButton> GetButtonsOfCommand();

	//This can range between 0 & 4
	void RegisterController(int index);
	Controller* GetController() const { return m_pController; }

	int GetControllerIndex() const { return m_ControllerID; }
private:
	std::unordered_map<Controller::ControllerButton, Command*> m_ControllerCommands{};
	null_InputManager* m_pInputManager;
	Controller* m_pController{};
	int m_ControllerID{};
	bool m_IsInitialized{ false };
};

template <typename T>
std::vector<Controller::ControllerButton> ControllerComponent::GetButtonsOfCommand()
{
	std::vector<Controller::ControllerButton> buttons;

	for (const auto& keyMap : m_ControllerCommands)
	{
		if (dynamic_cast<T>(keyMap.second))
		{
			buttons.emplace_back(keyMap.first);
		}
	}

	return buttons;
}
