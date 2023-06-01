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
#include "TriggerComponent.h"
#include "SnowBeeState.h"
#include "CountdownComponent.h"

//
//Attacking State
//
PengoState* AttackingState::HandleInput()
{
	if (m_TimeUntilIdle <= 0.f)
	{
		return new MovingState(m_pActor);
	}

	auto& serviceLocator = ServiceLocator::GetInstance();
	const auto& inputManager = serviceLocator.InputManager.GetService();

	if (const auto inputComponent = m_pActor->GetComponent<InputComponent>())
	{
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
			if (inputManager.GetController(controllerComp->GetControllerIndex())->IsPressed(button))
			{
				return new MovingState(m_pActor);
			}
		}
	}

	if (m_IsHit) { return new DyingState(m_pActor); }

	return nullptr;
}

void AttackingState::Update()
{
	m_TimeUntilIdle -= TimeM::GetInstance().GetDeltaTimeM();

	if (const auto triggerComp = m_pActor->GetComponent<TriggerComponent>())
	{

		//Gets all the colliding objects of the pengo Trigger
		for (const auto& collidingGameObject : triggerComp->GetCollidingObjects())
		{

			//Skips the Colliding objects that can be deleted or the pengo itself
			if (collidingGameObject->CanBeDeleted() || collidingGameObject == m_pActor) continue;


			//Checks if the colliding object has a trigger component
			if (const auto iceBlockTrigger = collidingGameObject->GetComponent<TriggerComponent>())
			{

				//checks if the colliding object with a trigger is the actual IceBlockTrigger
				if (iceBlockTrigger->GetTag() == "IceBlockTrigger")
				{
					if (const auto direction = m_pActor->GetComponent<DirectionComponent>())
					{
						//Move the move the IceBlock
						collidingGameObject->GetComponent<MoveComponent>()->SetCanMove(true);
						collidingGameObject->GetComponent<DirectionComponent>()->SetDirection(direction->GetDirection());

						//Store the IceBlock in the GameObjectStorage
						if (const auto gameObjectStorage = m_pActor->GetComponent<GameObjectStorage>())
						{
							gameObjectStorage->StoreGameObject(collidingGameObject);
						}

					}
				}
			}
		}
	}
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
	m_IsHit = IsHit(other, isTrigger);

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
	}

	if (m_IsHit) { return new DyingState(m_pActor); }

	return nullptr;
}

void MovingState::Update()
{

	//If there is is input reset the timer!
	m_TimeUntilIdle -= TimeM::GetInstance().GetDeltaTimeM();

}

void MovingState::OnCollision(GameObject* other, bool isTrigger, bool /*isSenderTrigger*/)
{
	m_IsHit = IsHit(other, isTrigger);
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
		if (spriteRenderer->IsAnimationFinished())
		{
			//++m_Animations;
			//if (m_Animations == 8)
			//{
			//	spriteRenderer->Pause();
			//	std::cout << "Dying animation finished" << std::endl;
			//}
		}
	}
}

void DyingState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	PengoState::OnCollision(other, isTrigger, isSenderTrigger);
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
	}

	if (const auto controllerComp = m_pActor->GetComponent<ControllerComponent>())
	{
		controllerComp->DisableInput();
	}

	ServiceLocator::GetInstance().AudioService.GetService().Play(2);


	//Somehow restart the level
}

//
//
//ALL STATES
void PengoState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{

}

bool PengoState::IsHit(GameObject* other, bool isTrigger)
{
	if (isTrigger) { return false; }

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

		if (other == m_pActor->GetComponent<GameObjectStorage>()->GetGameObject())
		{
			return false;
		}

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
	}

	if (m_IsHit) { return new DyingState(m_pActor); }

	return nullptr;
}

void IdleState::Update()
{
}

void IdleState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	PengoState::OnCollision(other, isTrigger, isSenderTrigger);
	m_IsHit = IsHit(other, isTrigger);
}

void IdleState::OnEnter()
{
	if (const auto spriteRenderer = m_pActor->GetComponent<SpriteRenderer>())
	{
		spriteRenderer->Pause();
		spriteRenderer->SetOffset({ 0,0 });
	}
}
