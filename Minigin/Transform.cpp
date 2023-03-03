#include "Transform.h"

#include <iostream>

#include "Texture2D.h"

Transform::Transform() : Component()
{
}

Transform::~Transform() = default;


void Transform::Update()
{
}

void Transform::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void Transform::LateUpdate()
{
}

void Transform::Render() const
{
}

const glm::vec2& Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(const glm::vec2& newPosition)
{
	m_position.x = newPosition.x;
	m_position.y = newPosition.y;
}
