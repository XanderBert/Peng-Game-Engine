#include "PacManComponent.h"

#include "Transform.h"

void PacManComponent::AttachObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void PacManComponent::NotifyObservers(GameEvent event, GameObject* object)
{
	for (const auto& observer : m_Observers)
	{
		observer->Notify(object, event);
	}
}