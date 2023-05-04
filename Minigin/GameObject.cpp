#include "Component.h"
#include "GameObject.h"

#include "Transform.h"


//Transform Component Is Allready Added Here
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
	const auto transformComponent = GetComponent<Transform>();

	if (pParent == nullptr)
	{
		transformComponent->SetLocalPosition(transformComponent->GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			const auto parentTransformComponent = pParent->GetComponent<Transform>();

			transformComponent->SetLocalPosition(transformComponent->GetLocalPosition() - parentTransformComponent->GetWorldPosition());
		}
		transformComponent->SetPositionDirty();
	}

	if (m_pParent)
	{
		//Remove itself as a child from the previous parent(if any).
		RemoveFromChildren(m_pParent);
	}

	//Set the given parent on itself.
	m_pParent = pParent;
	//Add itself as a child to the given parent.
	AddToChildVector(m_pParent);
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

void GameObject::AddToChildVector(GameObject* pParent)
{
	pParent->m_pChildren.emplace_back(this);
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
	std::erase_if(m_pComponents, [](const std::shared_ptr<Component>& component)
	{return component->CanBeDeleted();});
}