#include "IceBlockTrigger.h"

#include <iostream>

#include "BoxCollider.h"

IceBlockTrigger::IceBlockTrigger(GameObject* pParent)
{
	SetParent(pParent, false);

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_CollisionSize);
	collision->DebugRender(true);
}

IceBlockTrigger::~IceBlockTrigger()
{
	std::cout << "IceBlockTrigger::~IceBlockTrigger()\n";
}

void IceBlockTrigger::Update()
{
	GameObject::Update();
}

void IceBlockTrigger::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);
}
