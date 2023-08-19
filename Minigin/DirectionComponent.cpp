#include "DirectionComponent.h"

class GhostComponent;

DirectionComponent::DirectionComponent(GameObject* owner) : Component(owner)
{
}

DirectionComponent::~DirectionComponent() = default;

void DirectionComponent::Update()
{
	if (m_IsDirectionChanged)
	{
		m_IsDirectionChanged = false;
	}
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
	if (m_Direction == direction) return;

	m_PreviousDirection = m_Direction;
	m_Direction = direction;
	m_IsDirectionChanged = true;
}

void DirectionComponent::SetDirectionX(float x)
{
	if (m_Direction.x == x) return;

	m_PreviousDirection = m_Direction;
	m_Direction.x = x;
	m_IsDirectionChanged = true;
}

void DirectionComponent::SetDirectionY(float y)
{
	if (m_Direction.y == y) return;
	m_PreviousDirection = m_Direction;
	m_Direction.y = y;
	m_IsDirectionChanged = true;
}

glm::vec2 DirectionComponent::GetDirection() const
{
	return m_Direction;
}

glm::vec2 DirectionComponent::GetPreviousDirection() const
{
	return m_PreviousDirection;
}
