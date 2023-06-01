#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

class Scene;
class GameActor;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);

	void Update();
	void FixedUpdate(float fixedTimeMStep);
	void LateUpdate();
	void Render();

	Scene* GetActiveScene() const;
	void SetActiveScene(Scene* activeScene);
	Scene* GetSceneByName(const std::string& name) const;

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;

	std::vector<std::shared_ptr<Scene>> m_scenes;
	Scene* m_pActiveScene{};
};

