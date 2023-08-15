#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

InputManager::InputManager()
{}

InputManager::~InputManager()
{}

bool InputManager::ProcessInput()
{
	UpdateControllersInput();

	return UpdateKeyboardInput();
}

Controller* InputManager::AddController(int controllerIndex)
{
	m_pControllers.emplace_back(std::make_unique<Controller>(controllerIndex));
	return m_pControllers.back().get();
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

bool InputManager::IsLeftMouseButtonPressed() const
{
	int mouseX, mouseY;
	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	return (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
}

glm::vec2 InputManager::GetLeftMouseButtonPressed() const
{
	int mouseX, mouseY;
	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	if ((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0)
	{
		return glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	return glm::vec2();
}


void InputManager::UpdateControllersInput() const
{
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

		//Updates Imgui Input
		ImGui_ImplSDL2_ProcessEvent(&e);
	}



	return true;
}