#include "GameObjectEx.h"

GameObjectEx::GameObjectEx(GameObject* owner) : Component(owner)
, transform(TransformEx(owner))
, ID(0)
{
}

GameObjectEx::~GameObjectEx() = default;


void GameObjectEx::Update()
{
}

void GameObjectEx::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
{
}

void GameObjectEx::LateUpdate()
{
}

void GameObjectEx::Render()
{
}
