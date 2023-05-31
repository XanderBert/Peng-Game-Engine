#include "PengoLevel.h"
#include "ServiceLocator.h"
#include "WallManager.h"

PengoLevel::PengoLevel()
{
	auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();

	audioService.AddSound(1, "Sounds/ActStart.mp3");
	audioService.AddSound(2, "Sounds/ActOver.mp3");
	//audioService.AddSound(2, "Sounds/ActClear.mp3");
	//
	//
	//

	m_pWallManager = new WallManager();
	for (const auto wall : m_pWallManager->GetHorizontalWalls())
	{
		AddGameObject(wall);
	}

	for (const auto wall : m_pWallManager->GetVerticalWalls())
	{
		AddGameObject(wall);
	}

#ifndef _DEBUG
	audioService.Play(1);
#endif


}

PengoLevel::~PengoLevel()
{
	delete m_pWallManager;
}

void PengoLevel::AddGameObject(GameObject* pGameObject)
{
	m_pGameObjects.emplace_back(pGameObject);

}

void PengoLevel::AddGameObjectsToScene(Scene* pScene)
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		pScene->Add(pGameObject);
	}
}
