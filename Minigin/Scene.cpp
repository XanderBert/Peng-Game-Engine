#include "Scene.h"
#include "CollisionManager.h"
#include "GameActor.h"
#include "GameObject.h"



unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	m_objects.emplace_back(object);
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

std::vector<GameActor*> Scene::GetAllGameActors() const
{
	std::vector<GameActor*> gameActors{};

	for (auto& gameActor : m_objects)
	{
		if (typeid(gameActor.get()) == typeid(GameActor*))
		{
			gameActors.push_back(dynamic_cast<GameActor*>(gameActor.get()));
		}
	}

	return gameActors;
}

void Scene::Update()
{
	for (auto& object : m_objects)
	{
		object->Update();
		CollisionManager::GetInstance().Update();
	}
}

void Scene::FixedUpdate(float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_objects)
	{
		object->LateUpdate();
	}

	//std::erase_if(m_objects, [](const std::shared_ptr<GameObject>& object)
	//{
	//	return object.get()->CanBeDeleted();
	//});
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}