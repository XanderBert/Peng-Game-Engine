#include "PacManComponent.h"

#include "Transform.h"

void PacManComponent::Die()
{
	--m_Lives;
	m_pOwner->GetComponent<Transform>()->SetWorldPosition({8	,	8});
}
