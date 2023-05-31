#include "InputComponent.h"

#include "ServiceLocator.h"

InputComponent::InputComponent(GameObject* owner)
	: Component(owner)
	, m_pInputManager(&ServiceLocator::GetInstance().InputManager.GetService())
{
}

InputComponent::~InputComponent()
{
	for (const auto& command : m_KeyboardCommands)
	{
		delete command.second;
	}
}

void InputComponent::Update()
{
	if (!m_IsEnabled)
	{
		return;
	}

	for (const auto& command : m_KeyboardCommands)
	{
		if (m_pInputManager->GetButtonPressed(command.first))
		{
			command.second->Execute();
		}
	}

}

void InputComponent::AddBinding(SDL_Keycode key, Command* command)
{
	m_KeyboardCommands.insert(std::make_pair(key, command));
}

void InputComponent::EnableInput()
{
	m_IsEnabled = true;
}

void InputComponent::DisableInput()
{
	m_IsEnabled = false;
}
