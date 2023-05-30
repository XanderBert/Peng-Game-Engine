#include "ControllerComponent.h"
#include "ServiceLocator.h"

ControllerComponent::ControllerComponent(GameObject* owner)
	: Component(owner)
	, m_pInputManager(&ServiceLocator::GetInstance().InputManager.GetService())
{
}


void ControllerComponent::Update()
{
	const auto controller = m_pInputManager->GetController(m_ControllerID);

	for (const auto& command : m_ControllerCommands)
	{
		if (controller->IsPressed(command.first))
		{
			command.second->Execute();
		}
	}

}

void ControllerComponent::AddBinding(Controller::ControllerButton button, Command* command)
{

	m_ControllerCommands.emplace(button, command);
}

void ControllerComponent::SetControllerIndex(int index)
{

	if (index < 0 || index > 4)
	{
		throw std::runtime_error("Controller index out of range, It should be between 0 and 4");
	}


	m_ControllerID = index;

	const auto& controllers = ServiceLocator::GetInstance().InputManager.GetService().GetControllers();

	for (const auto& controller : controllers)
	{
		if (controller->GetControllerID() == index)
		{
			controller->SetActor(m_pOwner);
		}
	}

}
