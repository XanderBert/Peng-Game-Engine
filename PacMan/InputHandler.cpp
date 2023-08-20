#include "InputHandler.h"
#include "ControllerComponent.h"
#include <SDL_syswm.h>

#include "MoveCommand.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SkipLevelCommand.h"
#include "SwitchInputCommand.h"
#include "MuteCommand.h"

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
	//Multiplayer controller players cannot switch to keyboard

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
	m_OriginalController = IsPlayingWithController;


	//Movement
	m_pController->AddBinding(Controller::ControllerButton::DPadUp, new MoveCommand(m_pOwner, { 0,-1 }, InputType::Down));
	m_pController->AddBinding(Controller::ControllerButton::DPadRight, new MoveCommand(m_pOwner, { 1,0 }, InputType::Down));
	m_pController->AddBinding(Controller::ControllerButton::DPadDown, new MoveCommand(m_pOwner, { 0,1 }, InputType::Down));
	m_pController->AddBinding(Controller::ControllerButton::DPadLeft, new MoveCommand(m_pOwner, { -1,0 }, InputType::Down));
	m_pController->AddBinding(Controller::ControllerButton::Start, new SwitchInputCommand(m_pOwner, InputType::Down));


	//Movement
	m_pKeyboard->AddBinding(SDLK_w, new MoveCommand(m_pOwner, { 0,-1 }, InputType::Down));
	m_pKeyboard->AddBinding(SDLK_d, new MoveCommand(m_pOwner, { 1,0 }, InputType::Down));
	m_pKeyboard->AddBinding(SDLK_s, new MoveCommand(m_pOwner, { 0,1 }, InputType::Down));
	m_pKeyboard->AddBinding(SDLK_a, new MoveCommand(m_pOwner, { -1,0 }, InputType::Down));
	m_pKeyboard->AddBinding(SDLK_F1, new SkipLevelCommand(InputType::Pressed));
	m_pKeyboard->AddBinding(SDLK_m, new MuteCommand(InputType::Pressed));

	if (m_OriginalController) m_pKeyboard->DisableInput();
	else m_pController->DisableInput();

	if (m_OriginalController && m_Multiplayer) return;
	m_pKeyboard->AddBinding(SDLK_F2, new SwitchInputCommand(m_pOwner, InputType::Down));
}