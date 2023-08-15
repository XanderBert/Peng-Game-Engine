#include "StartScreenComponent.h"

#include "LevelLoader.h"
#include "ServiceLocator.h"

StartScreenComponent::StartScreenComponent(GameObject* pParent)
	: Component(pParent)
	, m_pInputManager(ServiceLocator::GetInstance().InputManager.GetService())
	, m_pCollisionManager(ServiceLocator::GetInstance().CollisionManager.GetService())
{







}


void StartScreenComponent::Update()
{
	const auto children = m_pOwner->GetChildren();
	const auto single = children[0];
	const auto vs = children[1];
	const auto coOp = children[2];


	if (m_pInputManager.IsLeftMouseButtonPressed())
	{
		if (auto collider = single->GetComponent<BoxCollider>().get())
		{
			if (m_pCollisionManager.IsInsideCollider(m_pInputManager.GetLeftMouseButtonPressed(), collider))
			{
				LevelLoader::GetInstance().LoadLevel(1, GameMode::SinglePlayer);
			}
		}

		if (auto collider = vs->GetComponent<BoxCollider>().get())
		{
			if (m_pCollisionManager.IsInsideCollider(m_pInputManager.GetLeftMouseButtonPressed(), collider))
			{
				LevelLoader::GetInstance().LoadLevel(1, GameMode::Vs);
			}
		}

		if (auto collider = coOp->GetComponent<BoxCollider>().get())
		{
			if (m_pCollisionManager.IsInsideCollider(m_pInputManager.GetLeftMouseButtonPressed(), collider))
			{
				LevelLoader::GetInstance().LoadLevel(1, GameMode::CoOp);
			}
		}

	}
}
