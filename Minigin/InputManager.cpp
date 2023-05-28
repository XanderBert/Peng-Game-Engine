#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

InputManager::InputManager()
{
	m_pControllers.push_back(std::make_unique<Controller>(0));
	m_pControllers.push_back(std::make_unique<Controller>(1));
}

InputManager::~InputManager()
{
	//for (const auto& command : m_KeyboardCommands)
	//{
	//	delete command.second;
	//}
}

bool InputManager::ProcessInput()
{
	//Reset the input
	m_Input = 0;

	//Check if a new controller is contected
	CheckIfControllerNeedsToBeAdded();

	//Update the controllers
	for (const auto& controller : m_pControllers)
	{
		controller->Update();
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		//Exit the game
		if (e.type == SDL_QUIT) { return false; }

		//Store when a key is pressed
		if (e.type == SDL_KEYDOWN)
		{
			m_Input = e.key.keysym.sym;

			//Execute the command for the corresponding key
			if (m_KeyboardCommands.contains(m_Input))
			{
				m_KeyboardCommands[m_Input]->Execute();
			}
		}
	}

	//Updates Imgui Input
	ImGui_ImplSDL2_ProcessEvent(&e);
	return true;
}

std::vector<Controller*> InputManager::GetUsedControllers()
{
	std::vector<Controller*> controllers{};

	for (const auto& controller : m_pControllers)
	{
		if (controller->GetIsInUse())
		{
			controllers.push_back(controller.get());
		}
	}
	return controllers;
}

std::vector<Controller*> InputManager::GetControllers()
{
	std::vector<Controller*> controllers{};

	for (const auto& controller : m_pControllers)
	{

		controllers.push_back(controller.get());

	}
	return controllers;
}

bool InputManager::GetButtonPressed(SDL_KeyCode key) const
{
	return key == m_Input;
}

bool InputManager::GetButtonPressed(int controllerId, Controller::ControllerButton controllerButton) const
{
	for (const auto& controller : m_pControllers)
	{
		if (controller.get()->GetControllerID() == controllerId)
		{
			return controller.get()->IsPressed(controllerButton);
		}
	}

	return false;
}

void InputManager::RegisterCommand(SDL_Keycode key, Controller::ControllerButton /*controllerButton*/, Command* command)
{
	m_KeyboardCommands.insert(std::make_pair(key, command));
	//m_ControllerCommands.insert(std::make_pair(controllerButton, command));
}

void InputManager::HandleInput(Controller::ControllerButton /*key*/)
{
	/*if (m_ControllerCommands.contains(key))
	{
		m_ControllerCommands[key]->Execute();
	}*/
}

void InputManager::CheckIfControllerNeedsToBeAdded()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	if (m_pControllers[0]->IsControllerConnectedOnPort(index))
	{
		m_pControllers.push_back(std::make_unique<Controller>(index));
	}
}
