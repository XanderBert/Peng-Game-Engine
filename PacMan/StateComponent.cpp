#include "StateComponent.h"

StateComponent::StateComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pState{ std::make_unique<PacManMoveState>(pOwner) }
{
}

void StateComponent::Update()
{
	if (State* newState = m_pState->HandleInput())
	{
		if (newState)
		{
			m_pState.reset(newState);
		}
	}

	m_pState->Update();
}

void StateComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void StateComponent::LateUpdate()
{
}

void StateComponent::Render()
{

}

void StateComponent::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	m_pState->OnCollision(other, isTrigger, isSenderTrigger);
}

void StateComponent::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	m_pState->OnCollisionEnter(other, isTrigger, isSenderTrigger);
}


void StateComponent::SetState(State* pState)
{
	m_pState.reset(pState);
}
