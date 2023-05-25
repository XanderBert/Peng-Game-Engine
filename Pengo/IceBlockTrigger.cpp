#include "IceBlockTrigger.h"

#include <iostream>

#include "BoxCollider.h"
#include "IceBlock.h"

IceBlockTrigger::IceBlockTrigger(IceBlock* pParent)
{
	SetParent(pParent, false);

	const auto offset = (m_CollisionSize - pParent->GetSpriteSize()) / 2.f; // will result in {2,2}

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_CollisionSize);
	collision->DebugRender(true);
	collision->SetColliderOffset(-offset);
}

IceBlockTrigger::~IceBlockTrigger()
{
}

void IceBlockTrigger::Update()
{
	GameObject::Update();
}

void IceBlockTrigger::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);
}