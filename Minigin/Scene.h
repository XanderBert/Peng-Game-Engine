#pragma once
#include "GameObject.h"
#include "SceneManager.h"

class GameObject;
class Scene final
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(GameObject* object);
	void Remove(GameObject* object);
	void RemoveAll();

	std::string GetName() const { return m_name; }
	std::vector<GameObject*> GetObjects() const;

	void Update();
	void FixedUpdate(float fixedTimeMStep);
	void LateUpdate();
	void Render() const;

	void MarkForDeletion();

	bool CanBeDeleted() const
	{
		return m_CanBeDeleted;
	}

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private:
	explicit Scene(const std::string& name);

	std::string m_name;
	std::vector < std::unique_ptr<GameObject>> m_objects{};

	static unsigned int m_idCounter;
	bool m_CanBeDeleted = false;
};