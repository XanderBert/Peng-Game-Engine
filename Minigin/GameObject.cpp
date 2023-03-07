#include "Component.h"
#include "GameObject.h"

GameObject::GameObject()
{
	
} 
GameObject::~GameObject() = default;

void GameObject::Update()
{
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
}

void GameObject::FixedUpdate(float fixedTimeStep)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(fixedTimeStep);
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

std::shared_ptr<GameObject> GameObject::GetParent() const
{
	return m_pParent;
}

void GameObject::SetParent(std::shared_ptr<GameObject>& pParent)
{
	if (pParent == nullptr)
	{
		//remove itself from child vector of previous parent
		//make world its new parent
	}
	else
	{
		//Remove itself as a child from the previous parent(if any).
		//Set the given parent on itself.
		//Add itself as a child to the given parent.
		//Update position, rotation and scale

		if(m_pParent)
		{
			
		}

		//add itself to children vector of the parent
		m_pParent = pParent;
		AddToChildVector(this);
	}
}
int GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::shared_ptr<GameObject> GameObject::GetChildAt(int index) const
{
	if(index >= 0 ||index < m_pChildren.size())
	{
		return m_pChildren[index];
	}

	return nullptr;
}

void GameObject::AddToChildVector(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void GameObject::RemoveFromChildren(GameObject* pChild, GameObject* pParent)
{
	for(auto it{pParent->m_pChildren.begin()->get()}; it != pParent->m_pChildren.end()->get(); ++it)
	{
		if(it == pChild)
		{
		
		}
	}
}

void GameObject::RemoveComponents()
{
	//Check if it can be deleted
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		const auto& component{ *it };
		if (component->CanBeDeleted())
		{
			const auto& index{ std::distance(m_pComponents.begin(), it) };
			m_pComponents[index].reset();
			m_pComponents.erase(it);
		}
	}
}