#include "PlayerState.h"
#include "Pengo.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "IceBlock.h"
//
//Attacking State
//
PlayerState* AttackingState::HandleInput()
{
	if (m_TimeUntilMoveState <= 0.f)
	{
		return new MovingState(m_pActor);
	}

	auto& serviceLocator = ServiceLocator::GetInstance();
	auto& inputManager = serviceLocator.InputManager.GetService();
	if (!m_pActor->GetUsesController())
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
		const glm::vec2 moving = inputManager.GetController(m_pActor->GetControllerIndex())->GetLeftThumbValue();
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
		for (auto& gameObject : m_pActor->GetCollidingObjects())
		{
			if (gameObject->CanBeDeleted()) continue;

			if (auto iceBlock = dynamic_cast<IceBlock*>(gameObject))
			{
				iceBlock->MoveIceBlock(spriteRenderer->GetMovementDirection());
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

void AttackingState::OnCollision()
{
}

//
//Moving State
//
PlayerState* MovingState::HandleInput()
{
	//TODO if event is triggered (Colliding with ice) -> return new AttackingState();
	auto& serviceLocator = ServiceLocator::GetInstance();
	auto& inputManager = serviceLocator.InputManager.GetService();

	if (!m_pActor->GetUsesController())
	{
		if (inputManager.GetButtonPressed(SDLK_SPACE))
		{
			return new AttackingState(m_pActor);
		}
	}
	else
	{
		if (inputManager.GetController(m_pActor->GetControllerIndex())->IsDown(Controller::ControllerButton::ButtonA))
		{
			return new AttackingState(m_pActor);
		}
	}

	return nullptr;
}

void MovingState::Update()
{
}

void MovingState::OnCollision()
{
}

void MovingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetOffset({ 0,0 });
	}
}
