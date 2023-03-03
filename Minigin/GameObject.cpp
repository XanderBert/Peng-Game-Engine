#include "Component.h"
#include "GameObject.h"

#include <iostream>

GameObject::GameObject() = default;
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

void GameObject::RemoveComponents()
{
	//Check if it can be deleted
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		const auto& component{ *it };
		if (component->CanBeDeleted())
		{
			const auto index{ std::distance(m_pComponents.begin(), it) };
			m_pComponents[index].reset();
			m_pComponents.erase(it);
		}
	}
}