#include "PengoLevel.h"
#include "ServiceLocator.h"
#include <iostream>

PengoLevel::PengoLevel()
{
	auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();

	audioService.AddSound(1, "Sounds/ActStart.mp3");
	audioService.AddSound(2, "Sounds/ActOver.mp3");
	//audioService.AddSound(2, "Sounds/ActClear.mp3");
	//
	//
	//


#ifndef _DEBUG
	audioService.Play(1);
#endif


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
