#include "PengoState.h"
#include "Pengo.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "IceBlock.h"
#include "IceBlockTrigger.h"


//Add Standstil State

//
//Attacking State
//
PengoState* AttackingState::HandleInput()
{
	if (m_TimeUntilMoveState <= 0.f)
	{
		return new MovingState(m_pActor);
	}

	auto& serviceLocator = ServiceLocator::GetInstance();
	auto& inputManager = serviceLocator.InputManager.GetService();

	if (!(dynamic_cast<Pengo*>(m_pActor)->GetUsesController()))
	{
		//Get the function pointer to the GetButtonPressed function
		auto buttonPressedFunction = [&](SDL_KeyCode keyCode) { return inputManager.GetButtonPressed(keyCode); };

		const bool isMoving = buttonPressedFunction(SDLK_w) || buttonPressedFunction(SDLK_a) || buttonPressedFunction(SDLK_s) || buttonPressedFunction(SDLK_d);
		if (isMoving)
		{
			return new MovingState(m_pActor);
		}
	}
	else
	{
		const glm::vec2 moving = inputManager.GetController(dynamic_cast<Pengo*>(m_pActor)->GetControllerIndex())->GetLeftThumbValue();
		bool isMoving = moving.x != 0.f || moving.y != 0.f;

		if (isMoving)
		{
			return new MovingState(m_pActor);
		}
	}

	return nullptr;
}

void AttackingState::Update()
{
	m_TimeUntilMoveState -= TimeM::GetInstance().GetDeltaTimeM();


	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		for (const auto& collidingGameObjects : dynamic_cast<Pengo*>(m_pActor)->GetPengoIceBlockTrigger()->GetCollidingObjects())
		{
			if (collidingGameObjects->CanBeDeleted()) continue;

			if (const auto iceBlockTrigger = dynamic_cast<IceBlockTrigger*>(collidingGameObjects))
			{
				const auto iceBlock = iceBlockTrigger->GetParent();
				if(const auto direction = iceBlock->GetComponent<DirectionComponent>())
				{
					//Move component!
					//Pengo Usually does not move when attacking so that means we don't have a valid direction
					dynamic_cast<IceBlock*>(iceBlock)->MoveIceBlock(direction->GetPreviousDirection());
				}
			}
		}
	}
}

void AttackingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetOffset({ 0,16 });
	}

	//Play attacking sound
	ServiceLocator::GetInstance().AudioService.GetService().Play(0);
}

void AttackingState::OnCollision(GameObject* /*other*/)
{
}

//
//Moving State
//
PengoState* MovingState::HandleInput()
{
	//TODO if event is triggered (Colliding with ice) -> return new AttackingState();
	auto& serviceLocator = ServiceLocator::GetInstance();
	auto& inputManager = serviceLocator.InputManager.GetService();

	if (!dynamic_cast<Pengo*>(m_pActor)->GetUsesController())
	{
		if (inputManager.GetButtonPressed(SDLK_SPACE))
		{
			return new AttackingState(m_pActor);
		}
	}
	else
	{
		if (inputManager.GetController(dynamic_cast<Pengo*>(m_pActor)->GetControllerIndex())->IsDown(Controller::ControllerButton::ButtonA))
		{
			return new AttackingState(m_pActor);
		}
	}

	return nullptr;
}

void MovingState::Update()
{
}

void MovingState::OnCollision(GameObject* /*other*/)
{
}

void MovingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetOffset({ 0,0 });
	}
}

void PengoState::OnCollision(GameObject* /*other*/)
{

}
