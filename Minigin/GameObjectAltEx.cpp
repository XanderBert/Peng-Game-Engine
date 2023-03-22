#include "GameObjectAltEx.h"

GameObjectAltEx::GameObjectAltEx(GameObject* owner) : Component(owner)
, ID(0)
, transform( new TransformEx(owner))
{
}

GameObjectAltEx::~GameObjectAltEx()
{
	delete transform;
}


void GameObjectAltEx::Update()
{
}

void GameObjectAltEx::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void GameObjectAltEx::LateUpdate()
{
}

void GameObjectAltEx::Render()
{
}
