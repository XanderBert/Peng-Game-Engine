#include "InputHandler.h"
#include "ControllerComponent.h"
#include <SDL_syswm.h>

#include "MoveCommand.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "SwitchInputCommand.h"

InputHandler::InputHandler(GameObject* pParent)
	: Component{ pParent }
	, m_pController{ pParent->AddComponent<ControllerComponent>().get() }
	, m_pKeyboard{ pParent->AddComponent<InputComponent>().get() }
{


	m_pController->RegisterController(m_ControllerID);


	//Check if there is already another Pacman
	const auto gameObjects = SceneManager::GetInstance().GetActiveScene()->GetObjects();

	for (const auto& object : gameObjects)
	{
		if (object->GetComponent<PacManComponent>() != nullptr)
		{
			//Set multiplayer to true
			object->GetComponent<InputHandler>()->SetMultiplayer(true);
			SetMultiplayer(true);
			++m_ControllerID;
		}
	}


}

void InputHandler::Update()
{
}

void InputHandler::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void InputHandler::LateUpdate()
{
}

void InputHandler::Render()
{
}

void InputHandler::SetupInput(const bool IsPlayingWithController)
{

	//Multiplayer
	if (m_Multiplayer)
	{
		if (IsPlayingWithController)
		{
			//Movement
			m_pController->AddBinding(Controller::ControllerButton::DPadUp, new MoveCommand(m_pOwner, { 0,-1 }));
			m_pController->AddBinding(Controller::ControllerButton::DPadRight, new MoveCommand(m_pOwner, { 1,0 }));
			m_pController->AddBinding(Controller::ControllerButton::DPadDown, new MoveCommand(m_pOwner, { 0,1 }));
			m_pController->AddBinding(Controller::ControllerButton::DPadLeft, new MoveCommand(m_pOwner, { -1,0 }));

			//Disable Keyboard
			m_pKeyboard->DisableInput();
		}
		else
		{
			//Movement
			m_pKeyboard->AddBinding(SDLK_w, new MoveCommand(m_pOwner, { 0,-1 }));
			m_pKeyboard->AddBinding(SDLK_d, new MoveCommand(m_pOwner, { 1,0 }));
			m_pKeyboard->AddBinding(SDLK_s, new MoveCommand(m_pOwner, { 0,1 }));
			m_pKeyboard->AddBinding(SDLK_a, new MoveCommand(m_pOwner, { -1,0 }));

			//Disable Controller
			m_pController->DisableInput();
		}

		return;
	}



	//Singleplayer
	if (IsPlayingWithController)
	{
		//Movement
		m_pController->AddBinding(Controller::ControllerButton::DPadUp, new MoveCommand(m_pOwner, { 0,-1 }));
		m_pController->AddBinding(Controller::ControllerButton::DPadRight, new MoveCommand(m_pOwner, { 1,0 }));
		m_pController->AddBinding(Controller::ControllerButton::DPadDown, new MoveCommand(m_pOwner, { 0,1 }));
		m_pController->AddBinding(Controller::ControllerButton::DPadLeft, new MoveCommand(m_pOwner, { -1,0 }));

		//Switch Input
		m_pController->AddBinding(Controller::ControllerButton::ButtonA, new SwitchInputCommand(m_pOwner));

		//Disable Keyboard
		m_pKeyboard->DisableInput();

	}
	else
	{
		//Movement
		m_pKeyboard->AddBinding(SDLK_w, new MoveCommand(m_pOwner, { 0,-1 }));
		m_pKeyboard->AddBinding(SDLK_d, new MoveCommand(m_pOwner, { 1,0 }));
		m_pKeyboard->AddBinding(SDLK_s, new MoveCommand(m_pOwner, { 0,1 }));
		m_pKeyboard->AddBinding(SDLK_a, new MoveCommand(m_pOwner, { -1,0 }));



		//Switch Input
		m_pKeyboard->AddBinding(SDLK_TAB, new SwitchInputCommand(m_pOwner));

		//Disable Controller
		m_pController->DisableInput();
	}


}
