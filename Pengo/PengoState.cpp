#include "PengoState.h"
#include "GameObjectStorage.h"
#include "ControllerComponent.h"
#include "Pengo.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "MoveComponent.h"
#include "DirectionComponent.h"
#include "InputComponent.h"
#include "SnowBee.h"
#include "SnowBeeState.h"
#include "CountdownComponent.h"
#include "ObserverComponent.h"

//
//Attacking State
//
PengoState* AttackingState::HandleInput()
{
	if (m_TimeUntilIdle <= 0.f)
	{

		return new MovingState(m_pActor);

	}

	if (m_IsHit) { return new DyingState(m_pActor); }

	return nullptr;
}

void AttackingState::Update()
{
	m_TimeUntilIdle -= TimeM::GetInstance().GetDeltaTimeM();
}

void AttackingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->Play();
		spriteRenderer->SetOffset({ 0,16 });
	}

	//Play attacking sound
	ServiceLocator::GetInstance().AudioService.GetService().Play(0);
}

void AttackingState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	if (other->GetTag() == "IceBlock" && isSenderTrigger)
	{
		if (!m_MovedIceBlock)
		{
			//Move the move the IceBlock
			other->GetComponent<MoveComponent>()->SetCanMove(true);
			other->GetComponent<DirectionComponent>()->SetDirection(m_pActor->GetComponent<DirectionComponent>()->GetDirection());

			//Store the IceBlock in the GameObjectStorage
			if (const auto gameObjectStorage = m_pActor->GetComponent<GameObjectStorage>())
			{
				gameObjectStorage->StoreGameObject(other);
			}

			m_MovedIceBlock = true;
		}
	}

	m_IsHit = IsHit(other, isTrigger, isSenderTrigger);

	if (other->GetTag() == "Wall" && isSenderTrigger)
	{
		other->GetComponent<SpriteRenderer>()->Play();
		other->GetComponent<CountdownComponent>()->Play();
	}
}




//
//Moving State
//
PengoState* MovingState::HandleInput()
{

	if (m_TimeUntilIdle <= 0.f)
	{
		return new IdleState(m_pActor);
	}

	auto& serviceLocator = ServiceLocator::GetInstance();
	const auto& inputManager = serviceLocator.InputManager.GetService();



	//When Using Keyboard
	if (const auto inputComponent = m_pActor->GetComponent<InputComponent>())
	{
		const std::vector<SDL_Keycode> keys = inputComponent->GetKeysOfCommand<MoveCommand*>();

		for (const auto key : keys)
		{
			if (inputManager.GetButtonPressed(key))
			{
				m_TimeUntilIdle = 0.3f;

			}
		}

		if (inputManager.GetButtonPressed(SDLK_SPACE))
		{
			return new AttackingState(m_pActor);
		}
	}
	//When Using Controller
	if (const auto controllerComp = m_pActor->GetComponent<ControllerComponent>())
	{
		const std::vector<Controller::ControllerButton> buttons = controllerComp->GetButtonsOfCommand<MoveCommand*>();

		for (const auto button : buttons)
		{
			if (inputManager.GetController(controllerComp->GetControllerIndex())->IsPressed(button))
			{
				m_TimeUntilIdle = 0.3f;
			}
		}

		if (inputManager.GetController(controllerComp->GetControllerIndex())->IsPressed(Controller::ControllerButton::ButtonA))
		{
			return new AttackingState(m_pActor);
		}
	}

	if (m_IsHit) { return new DyingState(m_pActor); }

	return nullptr;
}

void MovingState::Update()
{
	m_TimeUntilIdle -= TimeM::GetInstance().GetDeltaTimeM();

}

void MovingState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	m_IsHit = IsHit(other, isTrigger, isSenderTrigger);
}

void MovingState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->Play();
		spriteRenderer->SetOffset({ 0,0 });
	}
}


//
//
//Dying state
PengoState* DyingState::HandleInput()
{
	return nullptr;
}

void DyingState::Update()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->SetAnimationFrame(0);
	}
}

void DyingState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{

}

void DyingState::OnEnter()
{
	//Set Sprite to dying
	m_pActor->GetComponent<DirectionComponent>()->SetDirection({ 0,0 });
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->Play();
		spriteRenderer->SetOffset({ 0,0 });
		spriteRenderer->SetFrameTime(0.4f);
	}

	if (const auto inputComp = m_pActor->GetComponent<InputComponent>())
	{
		inputComp->DisableInput();
		m_pActor->GetComponent<ObserverComponent>()->NotifyObserver(m_pActor, GameEvent::PengoKeyboardKilled);
	}

	if (const auto controllerComp = m_pActor->GetComponent<ControllerComponent>())
	{
		controllerComp->DisableInput();
		m_pActor->GetComponent<ObserverComponent>()->NotifyObserver(m_pActor, GameEvent::PengoControllerKilled);
	}

	ServiceLocator::GetInstance().AudioService.GetService().Play(2);
}

//
//
//ALL STATES
bool PengoState::IsHit(GameObject* other, bool /*isTrigger*/, bool isSenderTrigger)
{
	if (isSenderTrigger) { return false; }

	if (const auto snowBee = dynamic_cast<SnowBee*>(other))
	{
		if (dynamic_cast<SnowBeeConcussedState*>(snowBee->GetState()))
		{
			return false;
		}

		if (dynamic_cast<SnowBeeDyingState*>(snowBee->GetState()))
		{
			return false;
		}

		return true;
	}

	if (other->GetTag() == "IceBlock")
	{
		//If it is the same iceblock as the one we are pushing
		if (other == m_pActor->GetComponent<GameObjectStorage>()->GetGameObject())
		{
			return false;
		}

		//if it is a moving iceblock
		if (other->GetComponent<SpriteRenderer>()->IsPlaying() || other->GetComponent<MoveComponent>()->CanMove())
		{
			return true;
		}
	}

	return false;
}

//
//
//IDLE STATE
PengoState* IdleState::HandleInput()
{

	auto& serviceLocator = ServiceLocator::GetInstance();
	auto& inputManager = serviceLocator.InputManager.GetService();

	if (const auto inputComponent = m_pActor->GetComponent<InputComponent>())
	{
		if (inputManager.GetButtonPressed(SDLK_SPACE))
		{
			return new AttackingState(m_pActor);
		}

		const std::vector<SDL_Keycode> keys = inputComponent->GetKeysOfCommand<MoveCommand*>();

		for (const auto key : keys)
		{
			if (inputManager.GetButtonPressed(key))
			{
				return new MovingState(m_pActor);

			}
		}
	}

	//When Using Controller
	if (const auto controllerComp = m_pActor->GetComponent<ControllerComponent>())
	{
		const std::vector<Controller::ControllerButton> buttons = controllerComp->GetButtonsOfCommand<MoveCommand*>();

		for (const auto button : buttons)
		{
			if (controllerComp->GetController()->IsDown(button))
			{
				return new MovingState(m_pActor);
			}
		}

		if (inputManager.GetController(controllerComp->GetControllerIndex())->IsPressed(Controller::ControllerButton::ButtonA))
		{
			return new AttackingState(m_pActor);
		}
	}

	if (m_IsHit) { return new DyingState(m_pActor); }

	return nullptr;
}

void IdleState::Update()
{
}

void IdleState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	m_IsHit = IsHit(other, isTrigger, isSenderTrigger);
}

void IdleState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->Pause();
		spriteRenderer->SetOffset({ 0,0 });
	}

}
