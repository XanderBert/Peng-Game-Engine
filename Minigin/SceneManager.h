#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
	Scene* GetSceneByName(const std::string& name) const;
	void Update();
	void FixedUpdate(float fixedTimeStep);
	void LateUpdate();
	void Render();
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_scenes;
};

