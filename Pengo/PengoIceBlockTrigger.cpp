#include "PengoIceBlockTrigger.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "SpriteRenderer.h"

PengoIceBlockTrigger::PengoIceBlockTrigger(GameObject* pParent)
{
	SetParent(pParent, false);

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_CollisionSize);
	//collision->DebugRender(true);
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
			const glm::vec2 movementDir = spriteRenderer->GetMovementDirectionVector();
			boxCollider->SetColliderOffset({ m_OffsetMultiplier * movementDir.x + m_Offset.x, m_OffsetMultiplier * movementDir.y + m_Offset.y });
		}
	}
}

void PengoIceBlockTrigger::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);
}
