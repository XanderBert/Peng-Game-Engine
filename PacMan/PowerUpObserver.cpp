#include "PowerUpObserver.h"

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
				object->GetComponent<StateComponent>()->SetState(new FrightenedState{ object });
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
		//Gain Points
		gameObject->GetComponent<GameObjectStorage>()->GetStoredObject()->GetComponent<ScoreComponent>()->IncreaseScore(200);

		gameObject->GetComponent<Transform>()->SetWorldPosition({ 68,90 });
		gameObject->GetComponent<StateComponent>()->SetState(new ChaseState(gameObject));

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
