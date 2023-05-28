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
}

float VelocityComponent::GetVelocity() const
{
	return m_Velocity;
}
