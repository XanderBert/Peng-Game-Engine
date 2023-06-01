#include "SceneManager.h"
#include "Scene.h"
#include "TimeM.h"
#include "ServiceLocator.h"

void SceneManager::Update()
{
	GetActiveScene()->Update();

	ServiceLocator::GetInstance().CollisionManager.GetService().Update();
}

void SceneManager::FixedUpdate(float fixedTimeMStep)
{
	GetActiveScene()->FixedUpdate(fixedTimeMStep);
}

void SceneManager::LateUpdate()
{
	GetActiveScene()->LateUpdate();
}

void SceneManager::Render()
{
	GetActiveScene()->Render();
}

Scene* SceneManager::GetActiveScene() const
{
	if (m_pActiveScene) return m_pActiveScene;

	return m_scenes[m_scenes.size() - 1].get();
}

void SceneManager::SetActiveScene(Scene* activeScene)
{
	m_pActiveScene = activeScene;
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.emplace_back(scene);
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

	return nullptr;
}
