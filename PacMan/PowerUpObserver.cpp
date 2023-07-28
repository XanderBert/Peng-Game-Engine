#include "PowerUpObserver.h"
#include "GhostState.h"
#include "GhostComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "StateComponent.h"
#include "PowerUpComponent.h"

void PowerUpObserver::Notify(GameObject* /*gameObject*/, GameEvent event)
{
	if(event == GameEvent::PowerUpEaten)
	{
		const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
		std::vector<GameObject*> ghosts;

		for (const auto& object : objects)
		{
			if (object->GetComponent<GhostComponent>())
			{
				object->GetComponent<StateComponent>()->SetState(new FrightenedState{ object });
			}
		}
	}
}

PowerUpObserver::~PowerUpObserver()
{
}
