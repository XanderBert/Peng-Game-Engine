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

void Transform::Render()
{
}

void Transform::SetLocalPosition(const glm::vec2& position)
{
	m_TranformMatrixLocal.get()[0][0][2] = position.x;
	m_TranformMatrixLocal.get()[0][1][2] = position.y;

	SetPositionDirty();
}

glm::vec2 Transform::GetLocalPosition() const
{
	return {m_TranformMatrixLocal.get()[0][0][2],m_TranformMatrixLocal.get()[0][1][2]};
}

void Transform::SetWorldPosition(const glm::vec2& position)
{
	m_TranformMatrixWorld.get()[0][0][2] = position.x;
	m_TranformMatrixWorld.get()[0][1][2] = position.y;
}

glm::vec2 Transform::GetWorldPosition(const GameObject* parent)
{
	if (m_IsPositionDirty) UpdateWorldPosition(parent);

	return { m_TranformMatrixWorld.get()[0][0][2],m_TranformMatrixWorld.get()[0][1][2] };
}

void Transform::SetPositionDirty()
{
	m_IsPositionDirty = true;
}

void Transform::SetLocalRotation(const glm::vec2& angle)
{
	//Rotate Over x
	m_TranformMatrixLocal.get()[0][1][1] *= cos(angle.x);
	m_TranformMatrixLocal.get()[0][1][2] *= -sin(angle.x);
	m_TranformMatrixLocal.get()[0][2][1] *= sin(angle.x);
	m_TranformMatrixLocal.get()[0][2][2] *= cos(angle.x);

	//Rotate over y
	m_TranformMatrixLocal.get()[0][0][0] *= cos(angle.y);
	m_TranformMatrixLocal.get()[0][0][2] *= sin(angle.y);
	m_TranformMatrixLocal.get()[0][2][0] *= -sin(angle.y);
	m_TranformMatrixLocal.get()[0][2][2] *= cos(angle.y);
	//TODO: i should rotate over z?
}

glm::vec2 Transform::GetLocalRotation() const
{
	return glm::vec2{};
}

void Transform::SetWorldRotation(const glm::vec2& angle)
{
	angle;
}

glm::vec2 Transform::GetWorldPosition() const
{
	return glm::vec2{};
}

void Transform::SetLocalScale(const glm::vec2& scale)
{
	m_TranformMatrixLocal.get()[0][0][0] = scale.x;
	m_TranformMatrixLocal.get()[0][1][1] = scale.y;
}

glm::vec2 Transform::GetLocalScale() const
{
	return glm::vec2{ m_TranformMatrixLocal.get()[0][0][0], m_TranformMatrixLocal.get()[0][1][0]};
}

void Transform::SetWorldScale(const glm::vec2 scale)
{
	m_TranformMatrixWorld.get()[0][0][0] = scale.x;
	m_TranformMatrixWorld.get()[0][1][1] = scale.y;
}

glm::vec2 Transform::GetWorldScale() const
{
	return glm::vec2{ m_TranformMatrixWorld.get()[0][0][0], m_TranformMatrixWorld.get()[0][1][1] };
}

void Transform::UpdateWorldPosition(const GameObject* parent)
{
	if (m_IsPositionDirty)
	{
		if (parent == nullptr)
		{
			m_TranformMatrixWorld = std::move(m_TranformMatrixLocal);

		}
		else
		{
			SetWorldPosition(parent->GetComponent<Transform>()->GetWorldPosition(parent->GetParent()) + GetLocalPosition());
		}
	}
	m_IsPositionDirty = false;
}
