#pragma once
#include "SceneManager.h"
#include "GameObject.h"
class Scene final
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(GameObject* object);
	void Remove(std::unique_ptr<GameObject> object);
	void RemoveAll();
	std::vector<GameActor*> GetAllGameActors() const;

	std::string GetName() const { return m_name; }

	void Update();
	void FixedUpdate(float fixedTimeStep);
	void LateUpdate();
	void Render() const;
	
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
};