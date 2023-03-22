#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"
#include "Command.h"

//Extend the InputManager so we can add commands to be executed when a certain keyboard  button or controller button is pressed.For this we need :
//
//An abstract command class as  we've seen in the pattern with an Execute function
//A method to add bind a command to a certain controller button or keyboard key and a certain keystate(down, up or pressed).
//Extra code in ProcessInput that gets the state of the controllers and keyboard and executes the required commands.
//To handle controller input you'll need to use XInput. Checkout the documentation hereLinks to an external site.. You can include XInput.h without any problem, but don't forget to add xinput.lib to your linker dependencies or you'll get linker errors.
//To handle keyboard input you can use the sdlLinks to an external site. or win32 Links to an external site.input functionality.
//We recommend wrapping the controller functionality in a controller / gamepad class




bool InputManager::ProcessInput()
{
	std::pair<unsigned, Controller::ControllerButton>  pair = std::make_pair(m_Controllers.at(0), Controller::ControllerButton::ButtonA);
	if (Controller::IsPressed(BUTTON_Y)) buttonX->Execute();
	//m_consoleCommands.at(Controller::ControllerButton::ButtonA);
	JumpCommand jump = JumpCommand();
	m_consoleCommands.insert_or_assign(pair, JumpCommand().Execute()
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
			

		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{ 

		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}