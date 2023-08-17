#include "PowerUpObserver.h"
#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "GhostState.h"
#include "GhostComponent.h"
#include "HealthComponent.h"
#include "LevelLoader.h"
#include "PacDotComponent.h"
#include "LevelLoader.h"
#include "PacManComponent.h"
#include "PowerUpComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "StateComponent.h"
#include "ScoreComponent.h"
#include "SpriteRenderer.h"
#include "Transform.h"


void PowerUpObserver::Notify(GameObject* gameObject, GameEvent event)
{
	if (event == GameEvent::PowerUpEaten)
	{
		ServiceLocator::GetInstance().AudioService.GetService().Play(2);
		const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();

		if (LevelLoader::GetInstance().GetGameMode() == GameMode::Vs)
		{
			//Set Other Pacman in Frightened State
			for (const auto& object : objects)
			{
				if (object->GetComponent<PacManComponent>() != nullptr && object != gameObject)
				{
					object->GetComponent<StateComponent>()->SetState(new PacManFrightenedState{ object });
				}
			}

		}
		else
		{
			//Set Ghosts in Frightened State

			for (const auto& object : objects)
			{
				if (object->GetComponent<GhostComponent>())
				{
					const auto state = object->GetComponent<StateComponent>();

					//Only change state if the ghost is not in the idle state && not in the frightened state
					if (typeid(*state->GetState()) != typeid(IdleState) && typeid(*state->GetState()) != typeid(WasEatenState))
					{
						object->GetComponent<StateComponent>()->SetState(new FrightenedState{ object });
					}
				}
			}
		}


		//Gain Points
		gameObject->GetComponent<ScoreComponent>()->IncreaseScore(50);

		if (IsLevelCompleted())
		{
			LoadNextLevel();
		}
	}

	else if (event == GameEvent::PacDotEaten)
	{
		//Gain Points
		gameObject->GetComponent<ScoreComponent>()->IncreaseScore(10);
		ServiceLocator::GetInstance().AudioService.GetService().Play(++m_PacDotEatenSoundIndex % 2);

		if (IsLevelCompleted())
		{
			LoadNextLevel();
		}
	}

	else if (event == GameEvent::GhostEaten)
	{
		ServiceLocator::GetInstance().AudioService.GetService().Play(3);
		ServiceLocator::GetInstance().AudioService.GetService().Play(4);

		gameObject->GetComponent<StateComponent>()->SetState(new WasEatenState{ gameObject });

		//Check how many ghosts are already eaten.
		auto ghostsEaten = 0;
		for (const auto gameObj : gameObject->GetScene()->GetObjects())
		{
			if (gameObj->GetComponent<GhostComponent>() != nullptr)
			{
				auto state = gameObj->GetComponent<StateComponent>()->GetState();

				if (typeid(*state) == typeid(WasEatenState))
				{
					++ghostsEaten;
				}
			}
		}


		//added score = 200 * 2^(ghosts eaten)
		const auto score = static_cast<int>(200 * std::pow(2, (ghostsEaten - 1)));

		//Fetch Pacman of the ghost storage, Update its score of that pacman
		gameObject->GetComponent<GameObjectStorage>()->GetStoredObject()->GetComponent<ScoreComponent>()->IncreaseScore(score);

		gameObject->GetComponent<GhostComponent>()->InitEyesSprites();
	}

	else if (event == GameEvent::PacManDied)
	{

		ServiceLocator::GetInstance().AudioService.GetService().Play(6);

		//Lose Lives Points
		gameObject->GetComponent<HealthComponent>()->TakeDamage(1);

		//Check if its game over
		if (gameObject->GetComponent<HealthComponent>()->IsDead()) LevelLoader::GetInstance().LoadEndingScreen();

		//Lose points
		gameObject->GetComponent<ScoreComponent>()->IncreaseScore(-100);

		//Teleport to start
		gameObject->GetComponent<Transform>()->SetWorldPosition(gameObject->GetComponent<PacManComponent>()->GetSpawnPos());
	}
}

PowerUpObserver::~PowerUpObserver()
{
}

bool PowerUpObserver::IsLevelCompleted()
{
	const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	auto amountOfDotsLeft = 0;


	//The last eaton pacdot or powerup is just marked for deletion, so it is still in the scene until next frame.
	//So i need to check if the scene has only 1 object left (or less then 2).
	for (const auto object : objects)
	{
		if (object->GetComponent<PacDotComponent>() != nullptr || object->GetComponent<PowerUpComponent>() != nullptr)
		{
			++amountOfDotsLeft;

			if (amountOfDotsLeft > 1)
			{
				return false;
			}
		}
	}


	return true;
}

void PowerUpObserver::LoadNextLevel()
{
	auto id = LevelLoader::GetInstance().GetLevelId();
	LevelLoader::GetInstance().LoadLevel(++id);
}
