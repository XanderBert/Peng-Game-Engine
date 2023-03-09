#include "Transform.h"
#include "Texture2D.h"

Transform::Transform(GameObject* owner) : Component(owner)
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

void Transform::SetLocalPosition(const glm::vec2& position)
{
	m_LocalPosition = position;


	SetPositionDirty();
}

glm::vec2 Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

void Transform::SetWorldPosition(const glm::vec2& position)
{
	m_WorldPosition = position;
}

glm::vec2 Transform::GetWorldPosition(GameObject* parent)
{
	if (m_IsPositionDirty) UpdateWorldPosition(parent);

	return m_WorldPosition;
}

void Transform::SetPositionDirty()
{
	m_IsPositionDirty = true;
}

void Transform::UpdateWorldPosition(GameObject* parent)
{
	if (m_IsPositionDirty)
	{
		if (parent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;

		}
		else
		{
			m_WorldPosition = parent->GetComponent<Transform>()->GetWorldPosition(parent->GetParent()) + m_LocalPosition;
		}
	}
	m_IsPositionDirty = false;
}