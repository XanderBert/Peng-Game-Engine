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
	//m_LocalPosition = position;
	m_TranformMatrixLocal = {	glm::vec3{m_TranformMatrixLocal[0][0], m_TranformMatrixLocal[0][1], position.x},
									glm::vec3{m_TranformMatrixLocal[1][0], m_TranformMatrixLocal[1][1], position.y},
									glm::vec3{m_TranformMatrixLocal[2][0], m_TranformMatrixLocal[2][1], 1.f} };

	SetPositionDirty();
}

glm::vec2 Transform::GetLocalPosition() const
{
	return {m_TranformMatrixLocal[0][2],m_TranformMatrixLocal[1][2]};
}

void Transform::SetWorldPosition(const glm::vec2& position)
{
	m_TranformMatrixWorld = {	glm::vec3{m_TranformMatrixWorld[0][0], m_TranformMatrixWorld[0][1], position.x},
									glm::vec3{m_TranformMatrixWorld[1][0], m_TranformMatrixWorld[1][1], position.y},
									glm::vec3{m_TranformMatrixWorld[2][0], m_TranformMatrixWorld[2][1], 1.f} };
}

glm::vec2 Transform::GetWorldPosition(GameObject* parent)
{
	if (m_IsPositionDirty) UpdateWorldPosition(parent);

	return { m_TranformMatrixWorld[0][2],m_TranformMatrixWorld[1][2] };
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
			m_TranformMatrixWorld = m_TranformMatrixLocal;

		}
		else
		{
			SetWorldPosition(parent->GetComponent<Transform>()->GetWorldPosition(parent->GetParent()) + GetLocalPosition());
		}
	}
	m_IsPositionDirty = false;
}