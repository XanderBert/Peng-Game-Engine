#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

InputManager::InputManager()
{
	m_pButtonA = new JumpCommand();
	m_pLeftThumbStick = new MoveCommand();
	m_pControllers.push_back(std::make_unique<Controller>(0));
}

InputManager::~InputManager()
{
	delete m_pButtonA;
	delete m_pLeftThumbStick;
}

bool InputManager::ProcessInput()
{
	for (const auto& controller : m_pControllers)
	{
		

		controller->Update();


		if (controller->GetIsInUse())
		{
			if (const int leftTriggerVal = static_cast<int>(controller->GetbLeftTriggerValue()))
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				std::cout << "Left Trigger Value: " << leftTriggerVal << "\n";
			}

			if (controller->IsDown(Controller::ControllerButton::ButtonA))
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> Pressed A\n";
				//m_pButtonA->Execute(*controller->GetGameActor(), {});
			}

			if (controller->IsDown(Controller::ControllerButton::LeftThumb))
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> Pressed LeftThumb\n";
				//m_pButtonA->Execute(*m_pActors[i]);
			}

			if (controller->IsDown(Controller::ControllerButton::Start))
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> Pressed Start\n";
			}

			//
			//Triggers
			//
			if (const int leftTriggerVal = static_cast<int>(controller->GetbLeftTriggerValue()))
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				std::cout << "Left Trigger Value: " << leftTriggerVal << "\n";
			}

			if (const int rightTriggerVal = static_cast<int>(controller->GetbRightTriggerValue()))
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				std::cout << "Right Trigger Value: " << rightTriggerVal << "\n";
			}

			//
			//Thumbstick
			//
			const glm::vec2 leftThumb = controller->GetLeftThumbValue();
			if (leftThumb.x || leftThumb.y)
			{
				//m_pLeftThumbStick->Execute(*controller->GetGameActor(), { leftThumb.x, -leftThumb.y });
			}

			if (const float rightThumbX = controller->GetRightThumbValue().x)
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				std::cout << "Right Thumb X Value: " << rightThumbX << "\n";
			}

			if (const float rightThumbY = controller->GetRightThumbValue().y)
			{
				std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				std::cout << "Right Thumb Y Value: " << rightThumbY << "\n";
			}
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{

		if (e.type == SDL_QUIT)
		{
			return false;
		}

		if (e.type == SDL_KEYDOWN)
		{

		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void InputManager::CheckIfControllerNeedsToBeAdded()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	if(m_pControllers[0]->IsControllerConnectedOnPort(index))
	{
		m_pControllers.push_back(std::make_unique<Controller>(index));
	}
}
