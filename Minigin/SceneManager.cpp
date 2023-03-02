#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update(float deltaT)
{
	for (auto& scene : m_scenes)
	{
		scene->Update(deltaT);
	}
}

void SceneManager::FixedUpdate(float fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void SceneManager::LateUpdate(float deltaT)
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate(deltaT);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
