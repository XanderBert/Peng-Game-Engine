#pragma once
#include <glm/vec2.hpp>
#include "Command.h"
#include "ControllerComponent.h"
#include "GameObject.h"
#include "InputComponent.h"

class SwitchInputCommand final : public Command
{
public:
	SwitchInputCommand(GameObject* gameActor)
		: m_GameActor(gameActor)
	{}

	~SwitchInputCommand() override = default;

	void Execute() override
	{
		if(m_GameActor->GetComponent<InputComponent>()->IsEnabled())
		{
			m_GameActor->GetComponent<InputComponent>()->DisableInput();
			m_GameActor->GetComponent<ControllerComponent>()->EnableInput();
		}
			
		else
		{
			m_GameActor->GetComponent<InputComponent>()->EnableInput();
			m_GameActor->GetComponent<ControllerComponent>()->DisableInput();
		}
	}
private:
	GameObject* m_GameActor;
};
