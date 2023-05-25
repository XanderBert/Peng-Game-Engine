#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

InputManager::InputManager()
{
	m_pButtonA = new AttackCommand();
	m_pLeftThumbStick = new MoveCommand();

	m_pControllers.push_back(std::make_unique<Controller>(0));
	m_pControllers.push_back(std::make_unique<Controller>(1));
}

InputManager::~InputManager()
{
	delete m_pButtonA;
	delete m_pLeftThumbStick;
}

bool InputManager::ProcessInput()
{
	m_Input = 0;

	CheckIfControllerNeedsToBeAdded();

	for (const auto& controller : m_pControllers)
	{
		controller->Update();

		if (controller->GetIsInUse())
		{
			if (const int leftTriggerVal = static_cast<int>(controller->GetbLeftTriggerValue()))
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				//std::cout << "Left Trigger Value: " << leftTriggerVal << "\n";
			}

			if (controller->IsDown(Controller::ControllerButton::ButtonA))
			{
				//td::cout << "Controller: " << controller->GetControllerID() << " -> Pressed A\n";
				//m_pButtonA->Execute(*controller->GetGameActor(), {});
				//controller->GetActor()->TakeDammage(1);
			}

			if (controller->IsDown(Controller::ControllerButton::ButtonB))
			{
				//controller->GetActor()->GainPoints(25);
			}

			if (controller->IsDown(Controller::ControllerButton::LeftThumb))
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> Pressed LeftThumb\n";
				//m_pButtonA->Execute(*m_pActors[i]);
			}

			if (controller->IsDown(Controller::ControllerButton::Start))
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> Pressed Start\n";
			}

			//
			//Triggers
			//
			if (const int leftTriggerVal = static_cast<int>(controller->GetbLeftTriggerValue()))
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				//std::cout << "Left Trigger Value: " << leftTriggerVal << "\n";
			}

			if (const int rightTriggerVal = static_cast<int>(controller->GetbRightTriggerValue()))
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				//std::cout << "Right Trigger Value: " << rightTriggerVal << "\n";
			}

			//
			//Thumbstick
			//
			const glm::vec2 leftThumb = controller->GetLeftThumbValue();
			if (leftThumb.x || leftThumb.y)
			{
				m_pLeftThumbStick->Execute(*controller->GetActor(), { leftThumb.x * 4, -leftThumb.y * 4 });
			}

			if (const float rightThumbX = controller->GetRightThumbValue().x)
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				//std::cout << "Right Thumb X Value: " << rightThumbX << "\n";
			}

			if (const float rightThumbY = controller->GetRightThumbValue().y)
			{
				//std::cout << "Controller: " << controller->GetControllerID() << " -> ";
				//::cout << "Right Thumb Y Value: " << rightThumbY << "\n";
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

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}

		for (const auto& actor : m_pActors)
		{
			if (!actor->GetUsesController())
			{
				if (e.type == SDL_KEYDOWN)
				{
					m_Input = e.key.keysym.sym;

					if (m_Input == SDLK_LEFT || m_Input == SDLK_a)
					{
						actor->Move({ -4, 0 });
					}
					if (m_Input == SDLK_RIGHT || m_Input == SDLK_d)
					{
						actor->Move({ 4, 0 });
					}
					if (m_Input == SDLK_UP || m_Input == SDLK_w)
					{
						actor->Move({ 0, -4 });
					}
					if (m_Input == SDLK_DOWN || m_Input == SDLK_s)
					{
						actor->Move({ 0, 4 });
					}
					if (m_Input == SDLK_0)
					{
						actor->TakeDammage(1);
					}
					if (m_Input == SDLK_1)
					{
						actor->GainPoints(25);
					}
					if (m_Input == SDLK_SPACE)
					{
						actor->Attack();
					}
				}
			}
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

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

void InputManager::CheckIfControllerNeedsToBeAdded()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	if (m_pControllers[0]->IsControllerConnectedOnPort(index))
	{
		m_pControllers.push_back(std::make_unique<Controller>(index));
	}
}
