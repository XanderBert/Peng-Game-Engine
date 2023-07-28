#include "PacManComponent.h"

#include "Transform.h"

void PacManComponent::Die()
{
	--m_Lives;
	m_pOwner->GetComponent<Transform>()->SetWorldPosition({8	,	8});
}

void PacManComponent::AttachObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void PacManComponent::NotifyObservers(GameEvent event)
{
    for (const auto& observer : m_Observers)
    {
        observer->Notify(m_pOwner, event);
    }
}