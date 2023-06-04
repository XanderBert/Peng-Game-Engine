#include "PengoLevel.h"
#include "Transform.h"
#include "FontRenderer.h"
#include "FPSCounter.h"
#include "ServiceLocator.h"
#include "WallManager.h"

class Transform;

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
	for (const auto wall : m_pWallManager->GetWalls())
	{
		AddGameObject(wall);
	}
	AddGameObject(m_pWallManager);



}

PengoLevel::~PengoLevel()
{

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
