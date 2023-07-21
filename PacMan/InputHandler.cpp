#include "InputHandler.h"

#include <SDL_syswm.h>

#include "MoveCommand.h"
#include "SwitchInputCommand.h"

InputHandler::InputHandler(GameObject* pParent)
	: Component{ pParent }
	, m_pController{ pParent->AddComponent<ControllerComponent>().get() }
	, m_pKeyboard{ pParent->AddComponent<InputComponent>().get() }
{

	
	//Movement
	m_pKeyboard->AddBinding(SDLK_w, new MoveCommand(pParent, { 0,-1 }));
	m_pKeyboard->AddBinding(SDLK_d, new MoveCommand(pParent, { 1,0 }));
	m_pKeyboard->AddBinding(SDLK_s, new MoveCommand(pParent, { 0,1 }));
	m_pKeyboard->AddBinding(SDLK_a, new MoveCommand(pParent, { -1,0 }));


	//Switch Input
	m_pKeyboard->AddBinding(SDLK_TAB, new SwitchInputCommand(pParent));


	m_pController->RegisterController(0);
	m_pController->DisableInput();
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
