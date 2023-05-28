#include "PengoIceBlockTrigger.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "DirectionComponent.h"

PengoIceBlockTrigger::PengoIceBlockTrigger(GameObject* pParent)
{
	SetParent(pParent, false);

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_CollisionSize);
}

PengoIceBlockTrigger::~PengoIceBlockTrigger()
{
}

void PengoIceBlockTrigger::Update()
{
	GameObject::Update();

	if (const auto spriteRenderer = GetParent()->GetComponent<SpriteRenderer>())
	{
		if (const auto boxCollider = GetComponent<BoxCollider>())
		{
			glm::vec2 direction = { 0,0 };

			if(const auto directionComponent = GetParent()->GetComponent<DirectionComponent>())
			{
				direction = directionComponent->GetDirection();
			}

			boxCollider->SetColliderOffset({ m_OffsetMultiplier * direction.x + m_Offset.x, m_OffsetMultiplier * direction.y + m_Offset.y });
		}
	}
}

void PengoIceBlockTrigger::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);
}
