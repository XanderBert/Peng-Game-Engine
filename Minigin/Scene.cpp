#include "Scene.h"
#include "ServiceLocator.h"
#include "GameObject.h"

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
}

Scene::~Scene()
{
	RemoveAll();
};

void Scene::Add(GameObject* object)
{
	object->SetScene(this);
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

	//std::erase(m_objects, object);
}

void Scene::RemoveAll()
{

	m_objects.clear();
}


std::vector<GameObject*> Scene::GetObjects() const
{
	std::vector<GameObject*> gameObjects;

	gameObjects.reserve(m_objects.size());

	for(const auto& gameObject : m_objects)
	{
		gameObjects.emplace_back(gameObject.get());
	}

	return gameObjects;
}

void Scene::Update()
{
	for (auto& object : m_objects)
	{
		if(object == nullptr) assert(false);

		object->Update();
	}
	ServiceLocator::GetInstance().CollisionManager.GetService().Update();
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

void Scene::MarkForDeletion()
{
	for (const auto& object : m_objects)
	{
		object->MarkForDeletion();

	}
	m_CanBeDeleted = true;
}
