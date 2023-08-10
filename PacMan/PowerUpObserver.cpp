#include "PowerUpObserver.h"

#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "GhostState.h"
#include "GhostComponent.h"
#include "HealthComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "StateComponent.h"
#include "ScoreComponent.h"
#include "Transform.h"


void PowerUpObserver::Notify(GameObject* gameObject, GameEvent event)
{
	if (event == GameEvent::PowerUpEaten)
	{
		//Set Ghosts in Frightened State
		const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
		for (const auto& object : objects)
		{
			if (object->GetComponent<GhostComponent>())
			{

				const auto state = object->GetComponent<StateComponent>();

				//Only change state if the ghost is not in the idle state
				if (typeid(*state->GetState()) != typeid(IdleState))
				{
					object->GetComponent<StateComponent>()->SetState(new FrightenedState{ object });
				}


			}
		}

		//Gain Points
		gameObject->GetComponent<ScoreComponent>()->IncreaseScore(50);
	}


	else if (event == GameEvent::PacDotEaten)
	{
		//Gain Points
		gameObject->GetComponent<ScoreComponent>()->IncreaseScore(10);
	}

	else if (event == GameEvent::GhostEaten)
	{

		//Fetch Pacman of the ghost storage, Update its score of that pacman
		gameObject->GetComponent<GameObjectStorage>()->GetStoredObject()->GetComponent<ScoreComponent>()->IncreaseScore(200);

		//Set the ghost back to its start position
		gameObject->GetComponent<Transform>()->SetWorldPosition(gameObject->GetComponent<GhostComponent>()->GetStartPosition());

		//Set the direction of the ghost upwards
		gameObject->GetComponent<DirectionComponent>()->SetDirection({ 0,-1 });

		//Set the according state of the ghost
		gameObject->GetComponent<StateComponent>()->SetState(gameObject->GetComponent<GhostComponent>()->GetRandomPossibleState());

	}

	else if (event == GameEvent::PacManDied)
	{
		//Gain Points
		gameObject->GetComponent<ScoreComponent>()->IncreaseScore(-100);
		gameObject->GetComponent<HealthComponent>()->TakeDamage(1);

	}
}

PowerUpObserver::~PowerUpObserver()
{
}
