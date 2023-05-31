#include "Scene.h"
#include "GameObject.h"
#include "ServiceLocator.h"


unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	m_objects.emplace_back(object);

	for (auto& child : object->GetChildren())
	{
		Add(child);
	}
}

void Scene::Remove(GameObject* object)
{
	for (auto& child : object->GetChildren())
	{
		Remove(child);
	}

	//	std::erase(m_objects, object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}


void Scene::Update()
{
	for (auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::FixedUpdate(float fixedTimeMStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeMStep);
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_objects)
	{
		object->LateUpdate();
	}


	//Handles Deletion of the GameObjects itself
	std::erase_if(m_objects, [](std::unique_ptr<GameObject>& object)
		{
			return object->CanBeDeleted();
		});
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}