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
	auto it = m_KeyStates.find(key);
	return it != m_KeyStates.end() && it->second;
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
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		//Exit the game
		if (e.type == SDL_QUIT) { return false; }

		// Store key states
		if (e.type == SDL_KEYDOWN)
		{
			m_KeyStates[e.key.keysym.sym] = true;
		}
		else if (e.type == SDL_KEYUP)
		{
			m_KeyStates[e.key.keysym.sym] = false;
		}


		//Updates Imgui Input
		ImGui_ImplSDL2_ProcessEvent(&e);
	}



	return true;
}