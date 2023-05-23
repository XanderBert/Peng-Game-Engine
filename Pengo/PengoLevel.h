#pragma once
#include "GameObject.h"
#include "Scene.h"

class PengoLevel final
{
public:
	PengoLevel() = default;
	~PengoLevel() = default;

	PengoLevel(const PengoLevel& other) = delete;
	PengoLevel(PengoLevel&& other)noexcept = delete;
	PengoLevel& operator=(const PengoLevel& other) = delete;
	PengoLevel& operator=(PengoLevel&& other)noexcept = delete;

	void AddGameObject(GameObject* pGameObject);
	void AddGameObjectsToScene(Scene* pScene);
private:
	std::vector<GameObject*> m_pGameObjects;
};
