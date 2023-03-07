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

//Once a owner has been set this function won't anything.
void Component::SetGameObject(GameObject* owner)
{
	//Prevents it from changing owner
	if (!m_pOwner)
	{
		m_pOwner = owner;
	}
}