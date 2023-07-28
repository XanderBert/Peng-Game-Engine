#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(GameObject* pOwner) : Component(pOwner)
{
}

void VelocityComponent::Update()
{
}

void VelocityComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void VelocityComponent::LateUpdate()
{
}

void VelocityComponent::Render()
{
}

void VelocityComponent::SetVelocity(float velocity)
{
	m_Velocity = velocity;
	m_InitialVelocity = velocity;
}

float VelocityComponent::GetVelocity() const
{
	return m_Velocity;
}

void VelocityComponent::SetVelocityPercentage(const float percentage)
{
	m_Velocity = m_InitialVelocity * (percentage / 100.f);
}
