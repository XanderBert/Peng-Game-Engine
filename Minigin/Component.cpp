#include "Component.h"

Component::Component() = default;

Component::~Component() = default;

void Component::MarkForDeletion()
{
	m_WillBeDeleted = true;
}

bool Component::CanBeDeleted() const
{
	return m_WillBeDeleted;
}

void Component::SetGameObject(GameObject* owner)
{
	if (!m_pOwner)
	{
		m_pOwner = owner;
	}
}