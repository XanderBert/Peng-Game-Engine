#include "PacManComponent.h"

#include "Transform.h"

void PacManComponent::AttachObserver(Observer* observer)
{
	m_pSubject->AttachObserver(observer);
}

void PacManComponent::Notify(GameEvent event, GameObject* object)
{
	m_pSubject->Notify(event, object);
}