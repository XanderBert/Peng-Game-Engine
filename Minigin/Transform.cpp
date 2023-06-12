#include "Transform.h"
#include "Texture2D.h"

Transform::Transform(GameObject* owner) : Component(owner)
{
}

Transform::~Transform() = default;


void Transform::Update()
{
}

void Transform::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
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
}


glm::vec2 Transform::GetLocalPosition()
{
	if (const auto parent = m_pOwner->GetParent())
	{
		auto parentWorldpos = parent->GetComponent<Transform>()->GetWorldPosition();

		return  (GetWorldPosition() - parentWorldpos);
	}

	return  GetWorldPosition();
}

void Transform::SetWorldPosition(const glm::vec2& position)
{
	m_LastTransformMatrixWorld = m_TranformMatrixWorld;

	if (const auto parent = m_pOwner->GetParent())
	{
		const auto parentTransComponent = parent->GetComponent<Transform>();
		const auto parentWorldPos = parentTransComponent->GetWorldPosition();
		const auto newLocalPos = position - parentWorldPos;

		m_TranformMatrixWorld[0][2] = newLocalPos.x;
		m_TranformMatrixWorld[1][2] = newLocalPos.y;
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

glm::vec2 Transform::GetLastWorldPosition()
{
	return glm::vec2{ m_LastTransformMatrixWorld[0][2], m_LastTransformMatrixWorld[1][2] };
}

void Transform::SetPositionDirty()
{
	m_IsPositionDirty = true;
}

void Transform::SetLocalRotation(const glm::vec2& /*angle*/)
{

}

glm::vec2 Transform::GetLocalRotation() const
{
	return glm::vec2{};
}

void Transform::SetWorldRotation(const glm::vec2& /*angle*/)
{
}

glm::vec2 Transform::GetWorldRotation() const
{
	return glm::vec2();
}

void Transform::SetLocalScale(const glm::vec2& /*scale*/)
{
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
