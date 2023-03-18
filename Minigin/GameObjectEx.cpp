#include "GameObjectEx.h"

GameObjectEx::GameObjectEx(GameObject* owner) : Component(owner)
, ID(0)
, transform(TransformEx(owner))
{
}

GameObjectEx::~GameObjectEx() = default;


void GameObjectEx::Update()
{
}

void GameObjectEx::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void GameObjectEx::LateUpdate()
{
}

void GameObjectEx::Render()
{
}
