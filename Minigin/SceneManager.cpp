#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"

void SceneManager::Update()
{
	for (auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void SceneManager::FixedUpdate(float fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
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

Scene* SceneManager::GetSceneByName(const std::string& name) const
{
	for (const auto& scene : m_scenes)
	{
		if (scene->GetName()._Equal(name))
		{
			return scene.get();
		}
	}


	//Todo: Throw error here
	return nullptr;
}
