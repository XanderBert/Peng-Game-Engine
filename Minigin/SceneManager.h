#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

class GameActor;
class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
	void Update();
	void FixedUpdate(float fixedTimeStep);
	void LateUpdate();
	void Render();
	std::vector<GameActor*> GetGameActorsOfScene(const std::string& sceneName) const;

	//TODO: temporary implementation scene
	Scene* GetActiveScene() const { return m_scenes[m_scenes.size() - 1].get(); }

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_scenes;
	Scene* GetSceneByName(const std::string& name) const;
};

