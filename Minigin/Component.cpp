#include "Component.h"
#include "GameObject.h"

Component::Component(int id): m_ID{id}
{

}

Component::~Component()
{
}

void Component::Update([[maybe_unused]]float deltaT)
{
}

void Component::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void Component::LateUpdate([[maybe_unused]] float deltaT)
{
}

void Component::Render() const
{
}

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
	if(owner == nullptr)
	{
		m_pOwner = owner;
	}
}