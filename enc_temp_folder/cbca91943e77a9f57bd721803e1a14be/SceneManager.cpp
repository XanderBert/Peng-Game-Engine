#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

void dae::SceneManager::Update(float deltaT)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaT);
	}
	std::cout << "UPDATE\n";
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	std::cout << "\n\nFixedUPDATE\n\n";
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}

}

void dae::SceneManager::LateUpdate(float deltaT)
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate(deltaT);
	}
	std::cout << "LateUPDATE\n";
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
