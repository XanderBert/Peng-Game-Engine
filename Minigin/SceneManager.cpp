#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void SceneManager::Update()
{
	GetActiveScene()->Update();
}

void SceneManager::FixedUpdate(float fixedTimeMStep)
{
	GetActiveScene()->FixedUpdate(fixedTimeMStep);
}

void SceneManager::LateUpdate()
{

	//Here we will Go over all the scene so that old scenes are properly deleted
	for (const auto& scene : m_scenes)
	{

		scene->LateUpdate();

		if (scene->CanBeDeleted())
		{
			//delete scene.get();
		}
	}
}

void SceneManager::Render()
{
	GetActiveScene()->Render();
}

Scene* SceneManager::GetActiveScene() const
{
	assert(!m_scenes.empty() && "There are no active scenes.");

	if (m_pActiveScene) return m_pActiveScene;

	if (m_scenes.empty()) return nullptr;

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

	throw std::exception("Scene not found");
}
