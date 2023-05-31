#include "MoveComponent.h"

#include "DirectionComponent.h"
#include "TimeM.h"
#include "Transform.h"
#include "VelocityComponent.h"

MoveComponent::MoveComponent(GameObject* pOwner) : Component(pOwner)
{
}

void MoveComponent::Update()
{
	if (m_CanMove)
	{
		const auto direction = m_pOwner->GetComponent<DirectionComponent>();
		const auto velocity = m_pOwner->GetComponent<VelocityComponent>();
		const auto transform = m_pOwner->GetComponent<Transform>();

		if (direction && velocity && transform)
		{
			const auto movement{ direction->GetDirection() * velocity->GetVelocity() * TimeM::GetInstance().GetDeltaTimeM() };
			transform->SetWorldPosition(transform->GetWorldPosition() + movement);
		}
	}
}

void MoveComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void MoveComponent::LateUpdate()
{
}

void MoveComponent::Render()
{
}

void MoveComponent::SetCanMove(bool canMove)
{
	m_CanMove = canMove;
}

bool MoveComponent::CanMove() const
{
	return m_CanMove;
}

void MoveComponent::ResetMovement()
{
	if (const auto transform = m_pOwner->GetComponent<Transform>())
	{
		if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
		{
			transform->SetWorldPosition(transform->GetLastWorldPosition() + (-directionComponent->GetDirection() * m_TunnelingMulitplier));
		}
	}
}

void MoveComponent::SetTunnelingMultiplier(float multiplier)
{
	m_TunnelingMulitplier = multiplier;
}

float MoveComponent::GetTunnelingMultiplier() const
{
	return m_TunnelingMulitplier;
}
