#include "ControllerComponent.h"
#include "ServiceLocator.h"
#include "VelocityComponent.h"
#include "InputManager.h"

ControllerComponent::ControllerComponent(GameObject* owner)
	: Component(owner)
	, m_pInputManager(&ServiceLocator::GetInstance().InputManager.GetService())
{
}

ControllerComponent::~ControllerComponent()
{
	for (const auto& command : m_ControllerCommands)
	{
		delete command.second;
	}
}


void ControllerComponent::Update()
{
	if (!m_IsInitialized)
	{
		throw std::runtime_error("ControllerComponent not initialized\nCall The RegisterController(int index) Function");
	}


	if (!m_IsEnabled)
	{
		return;
	}

	for (const auto& command : m_ControllerCommands)
	{
		if (m_pController->IsPressed(command.first))
		{
			command.second->Execute();
			return;
		}
	}
}

void ControllerComponent::AddBinding(Controller::ControllerButton button, Command* command)
{
	m_ControllerCommands.emplace(button, command);
}

void ControllerComponent::RegisterController(int index)
{
	if (index < 0 || index > 4)
	{
		throw std::runtime_error("Controller index out of range, It should be between 0 and 4");
	}

	m_ControllerID = index;
	m_pController = m_pInputManager->AddController(m_ControllerID);
	m_IsInitialized = true;

	//TODO
	//const auto velocity = m_pOwner->GetComponent<VelocityComponent>()->GetVelocity();
	//m_pOwner->GetComponent<VelocityComponent>()->SetVelocity(velocity / 2.f);
}

void ControllerComponent::EnableInput()
{
	m_IsEnabled = true;
}

void ControllerComponent::DisableInput()
{
	m_IsEnabled = false;
}
