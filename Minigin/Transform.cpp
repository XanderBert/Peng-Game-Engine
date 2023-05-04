#include "Transform.h"

#include <iostream>

#include "Texture2D.h"

//The SetLocalRotation function applies rotations to the local transform matrix,
//but it does not set the dirty flag.This can cause issues with the world position updates.

//The GetLocalRotation function returns a zero vector.
//This means that it does not actually return the local rotation of the transform.

//The SetWorldRotation function does not actually rotate the transform matrix.
//It only takes the angle parameter and does nothing with it.

//The GetWorldPosition function does not take a parent parameter.
//This means that it always returns the world position relative to the parent GameObject,
//even if the parent GameObject is null.

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
	//Get parent world and add this

	if (const auto parent = m_pOwner->GetParent())
	{
		const auto parentWorldpos = parent->GetComponent<Transform>()->GetWorldPosition();

		SetWorldPosition(parentWorldpos + position);
	}
	else
	{
		SetWorldPosition(position);
	}

	SetPositionDirty();
}

glm::vec2 Transform::GetLocalPosition()
{

	if (const auto parent = m_pOwner->GetParent())
	{
		auto parentWorldpos = parent->GetComponent<Transform>()->GetWorldPosition();
		return  GetWorldPosition() - parentWorldpos;
	}

	return  GetWorldPosition();
}

void Transform::SetWorldPosition(const glm::vec2& position)
{
	if (const auto parent = m_pOwner->GetParent())
	{
		const auto parentTransComponent = parent->GetComponent<Transform>();
		const auto parentWorldPos = parentTransComponent->GetWorldPosition();
		const auto newLocalPos = position - parentWorldPos;

		m_TranformMatrixWorld[0][2] = newLocalPos.x;
		m_TranformMatrixWorld[1][2] = newLocalPos.y;

		//SetLocalPosition(newLocalPos);
	}
	else
	{
		m_TranformMatrixWorld[0][2] = position.x;
		m_TranformMatrixWorld[1][2] = position.y;
	}
}

glm::vec2 Transform::GetWorldPosition()
{
	UpdateWorldPosition();

	glm::vec2 worldPos{ m_TranformMatrixWorld[0][2], m_TranformMatrixWorld[1][2] };
	const GameObject* parent = m_pOwner->GetParent();

	while (parent)
	{
		const auto parentTransform = parent->GetComponent<Transform>();
		worldPos += parentTransform->GetLocalPosition();
		parent = parent->GetParent();
	}

	return worldPos;
}

void Transform::SetPositionDirty()
{
	m_IsPositionDirty = true;
}

void Transform::SetLocalRotation(const glm::vec2& angle)
{
	//Rotate Over x
	angle;
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

glm::vec2 Transform::GetWorldRotation() const
{
	return glm::vec2();
}

void Transform::SetLocalScale(const glm::vec2& scale)
{
	scale;
	//m_TranformMatrixLocal[0][0] = scale.x;
	//m_TranformMatrixLocal[1][1] = scale.y;
}

glm::vec2 Transform::GetLocalScale() const
{
	return glm::vec2{ };
}

void Transform::SetWorldScale(const glm::vec2 scale)
{
	m_TranformMatrixWorld[0][0] = scale.x;
	m_TranformMatrixWorld[1][1] = scale.y;
}

glm::vec2 Transform::GetWorldScale() const
{
	return glm::vec2{ m_TranformMatrixWorld[0][0], m_TranformMatrixWorld[1][1] };
}

void Transform::UpdateWorldPosition()
{
	if (const auto parent = m_pOwner->GetParent())
	{
		const auto parentTransformComponent = parent->GetComponent<Transform>().get();

		if (parentTransformComponent->IsPositionDirty() || m_IsPositionDirty)
		{
			_UpdateWorldPosition(parentTransformComponent);
		}
	}

	m_IsPositionDirty = false;
}

void Transform::_UpdateWorldPosition(Transform* parentTransComponent)
{
	SetWorldPosition(parentTransComponent->GetWorldPosition());
}
