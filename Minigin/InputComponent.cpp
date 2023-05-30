#include "InputComponent.h"

#include "ServiceLocator.h"

InputComponent::InputComponent(GameObject* owner)
	: Component(owner)
	, m_pInputManager(&ServiceLocator::GetInstance().InputManager.GetService())
{
}

void InputComponent::Update()
{
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
