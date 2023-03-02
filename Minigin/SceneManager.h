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

	void Update([[maybe_unused]] float deltaT);
	void FixedUpdate([[maybe_unused]] float fixedTimeStep);
	void LateUpdate([[maybe_unused]] float deltaT);
	void Render();
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_scenes;
};

