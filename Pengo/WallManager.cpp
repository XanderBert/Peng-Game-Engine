#include "WallManager.h"

#include <algorithm>

#include "BoxCollider.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Wall.h"


WallManager::WallManager()
	:m_WallCoordinates{{50,74},{50,58},{50,66},{50,50}}
{
	//Get the collider sizes from map.
	//Add collisions to wall -> Collision detection could happen on a wall then and not on a wall manager wich makes more sense

	GetComponent<Transform>()->SetWorldPosition(m_WallCoordinates[0]);

	const auto scene = SceneManager::GetInstance().GetActiveScene();
	for (const auto wallCoord : m_WallCoordinates)
	{
		const auto wallChild = new Wall();
		wallChild->GetComponent<Transform>()->SetLocalPosition(wallCoord);
		//wallChild->SetParent(this, false);
		scene->Add(wallChild);

		m_Walls.push_back(wallChild);
	}

	const auto wallCollider = m_Walls[m_Walls.size() - 1 ]->AddComponent<BoxCollider>();
	wallCollider->SetColliderSize({ 8, 32 });
	//wallCollider->DebugRender(true);
}

WallManager::~WallManager()
{
}
