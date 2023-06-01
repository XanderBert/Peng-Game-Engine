#include "GameObjectStorage.h"

GameObjectStorage::GameObjectStorage(GameObject* pOwner)
	: Component(pOwner)
{
}

GameObjectStorage::~GameObjectStorage()
{
}

void GameObjectStorage::Update()
{
}

void GameObjectStorage::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void GameObjectStorage::LateUpdate()
{
}

void GameObjectStorage::Render()
{
}

void GameObjectStorage::StoreGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}
