#include "FruitComponent.h"

#include "PacManComponent.h"

FruitComponent::FruitComponent(GameObject* pParent) : Component(pParent)
{
}

void FruitComponent::OnCollision(GameObject* gameObject, bool /*cond*/, bool /*cond1*/)
{
	if (gameObject->GetComponent<PacManComponent>())
	{
		gameObject->GetComponent<PacManComponent>()->NotifyObservers(GameEvent::FruitEaten, gameObject);
		m_pOwner->MarkForDeletion();
	}
}
