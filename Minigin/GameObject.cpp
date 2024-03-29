#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "ServiceLocator.h"
#include "BoxCollider.h"
GameObject::GameObject()

{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	for (const auto& component : m_pComponents)
	{
		component->MarkForDeletion();
	}
};

void GameObject::Update()
{
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
}

void GameObject::FixedUpdate(float fixedTimeMStep)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(fixedTimeMStep);
	}
}

void GameObject::LateUpdate()
{
	for (const auto& component : m_pComponents)
	{
		component->LateUpdate();
	}

	RemoveComponents();
}

void GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition = true)
{
	if (m_pParent == pParent)
	{
		return;
	}

	if (m_pParent)
	{
		// Remove from current parent's child list
		m_pParent->RemoveFromChildren(this);
	}

	m_pParent = pParent;

	if (m_pParent)
	{
		// Add to new parent's child list
		m_pParent->AddToChildVector(this);

		if (keepWorldPosition)
		{
			// Calculate the difference between the current world position and the new parent's world position
			glm::vec2 worldPosDiff = GetComponent<Transform>()->GetWorldPosition() - m_pParent->GetComponent<Transform>()->GetWorldPosition();

			// Set the local position of the child so that its world position remains the same
			GetComponent<Transform>()->SetLocalPosition(worldPosDiff);
		}
	}
}
int GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

GameObject* GameObject::GetChildAt(int index) const
{
	if (index >= 0 || static_cast<size_t>(index) < m_pChildren.size())
	{
		return m_pChildren[index];
	}

	return nullptr;
}

std::vector < GameObject*> GameObject::GetChildren() const
{
	return m_pChildren;
}

void GameObject::MarkForDeletion()
{
	//Mark All the member components for deletion
	for (const auto& component : m_pComponents)
	{
		component->MarkForDeletion();
	}

	//Call this function on its children
	for (const auto& child : m_pChildren)
	{
		child->MarkForDeletion();
	}

	m_CanBeDeleted = true;

}

void GameObject::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	for (const auto& component : m_pComponents)
	{
		component->OnCollision(other, isTrigger, isSenderTrigger);
	}
}

void GameObject::OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger)
{
	for (const auto& component : m_pComponents)
	{
		component->OnCollisionEnter(other, isTrigger, isSenderTrigger);
	}
}

std::set<GameObject*> GameObject::GetCollidingObjects() const
{
	if (GetComponent<BoxCollider>() == nullptr)
		return std::set<GameObject*>();

	return GetComponent<BoxCollider>()->GetCollidingGameObjects();
}

void GameObject::AddToChildVector(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void GameObject::RemoveFromChildren(GameObject* pParent) const
{
	//will remove the child that needs to be removed from the parent
	std::erase_if(pParent->m_pChildren, [this](const GameObject* child)
		{
			return child == this;
		});
}

void GameObject::RemoveComponents()
{
	// Remove components that can be deleted
	//Does it get deleted out of the vector?
	//the memory does gets freed.
	if (m_pComponents.size() > 0)
		std::erase_if(m_pComponents, [](const std::shared_ptr<Component>& component)
			{
				return component->CanBeDeleted();

			});
}

void GameObject::MarkComponentForDeletionUtility(Component* component) const
{
	component->MarkForDeletion();
}
