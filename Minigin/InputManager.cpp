#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

InputManager::InputManager()
{
	m_pControllers.push_back(std::make_unique<Controller>(0));
	m_pControllers.push_back(std::make_unique<Controller>(1));
}

InputManager::~InputManager()
{}

bool InputManager::ProcessInput()
{
	UpdateControllersInput();
	return UpdateKeyboardInput();
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

bool InputManager::GetButtonPressed(SDL_Keycode key) const
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


void InputManager::UpdateControllersInput()
{
	//Check if a new controller is contected
	CheckIfControllerNeedsToBeAdded();

	//Update the controllers
	for (const auto& controller : m_pControllers)
	{
		controller->Update();
	}
}

bool InputManager::UpdateKeyboardInput()
{
	//Reset the input
	m_Input = 0;
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		//Exit the game
		if (e.type == SDL_QUIT) { return false; }

		//Store when a key is pressed
		if (e.type == SDL_KEYDOWN)
		{
			m_Input = e.key.keysym.sym;
		}
	}

	//Updates Imgui Input
	ImGui_ImplSDL2_ProcessEvent(&e);

	return true;
}

void InputManager::CheckIfControllerNeedsToBeAdded()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	if (m_pControllers[0]->IsControllerConnectedOnPort(index))
	{
		m_pControllers.push_back(std::make_unique<Controller>(index));
	}
}
