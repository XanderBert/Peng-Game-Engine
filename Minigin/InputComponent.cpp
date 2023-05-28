#include "InputComponent.h"

#include "ServiceLocator.h"

InputComponent::InputComponent(GameObject* owner)
	: Component(owner)
	, m_pInputManager(&ServiceLocator::GetInstance().InputManager.GetService())
{
}

void InputComponent::AddBinding(SDL_Keycode key, Command* command)
{
	m_pInputManager->RegisterCommand(key, command);
}
