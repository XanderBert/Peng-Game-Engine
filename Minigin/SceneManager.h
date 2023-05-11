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
	virtual Scene& CreateScene(const std::string& name);
	virtual void Update();
	virtual void FixedUpdate(float fixedTimeMStep);
	virtual void LateUpdate();
	virtual void Render();
	virtual std::vector<GameActor*> GetGameActorsOfScene(const std::string& sceneName) const;
	virtual Scene* GetActiveScene() const { return m_scenes[m_scenes.size() - 1].get(); }

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_scenes;
	Scene* GetSceneByName(const std::string& name) const;
};

