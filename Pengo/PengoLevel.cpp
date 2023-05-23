#include "PengoLevel.h"

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
