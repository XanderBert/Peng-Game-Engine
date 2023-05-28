#include "DirectionComponent.h"

DirectionComponent::DirectionComponent(GameObject* owner) : Component(owner)
{
}

DirectionComponent::~DirectionComponent() = default;

void DirectionComponent::Update()
{
}

void DirectionComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void DirectionComponent::LateUpdate()
{
}

void DirectionComponent::Render()
{
}

void DirectionComponent::SetDirection(const glm::vec2& direction)
{
	m_PreviousDirection = m_Direction;
	m_Direction = direction;
}

void DirectionComponent::SetDirectionX(float x)
{
	m_PreviousDirection = m_Direction;
	m_Direction.x = x;
}

void DirectionComponent::SetDirectionY(float y)
{
	m_PreviousDirection = m_Direction;
	m_Direction.y = y;
}

glm::vec2 DirectionComponent::GetDirection() const
{
	return m_Direction;
}

glm::vec2 DirectionComponent::GetPreviousDirection() const
{
	return m_PreviousDirection;
}
