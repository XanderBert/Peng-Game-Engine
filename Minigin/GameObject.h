#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

class Component;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	//Called each frame
	virtual void Update();

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep);

	//Called after the Update()c
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate();

	//Called each frame
	virtual void Render() const;


	//
	//Components
	template <typename T> std::shared_ptr <T> AddComponent();
	template <typename T> std::shared_ptr<T> GetComponent() const;
	std::vector<std::shared_ptr<Component>> m_pComponents{};

	//
	//SceneGraph
	void SetParent(std::shared_ptr<GameObject>& pParent, bool keepWorldPosition);
	int GetChildCount() const;
	std::shared_ptr<GameObject> GetParent() const;
	std::shared_ptr<GameObject> GetChildAt(int index) const;

private:
	std::shared_ptr<GameObject> m_pParent{};
	//todo use unique? or use raw pointers
	//Do i need shared ownership?
	//Does this update need to go the children update or does the scene go over all possible game objects?
	//I think i will go over objects in scene that are in root
	//go over all children in the game objects
	//this way the scene will just become a game object at the top root
	std::vector<std::shared_ptr<GameObject>> m_pChildren{};

	void AddToChildVector(GameObject* pParent);
	void RemoveFromChildren(GameObject* pParent) const;
	//Gets called every late update
	//Removes all components that have been marked for deletion
	void RemoveComponents();
};

template<typename T>
std::shared_ptr <T> GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>(), "This class is not a component.");

	auto pComponent = std::make_shared<T>(this);

	m_pComponents.emplace_back(pComponent);

	return dynamic_pointer_cast<T>(m_pComponents.back());
}

template<typename T>
std::shared_ptr<T> GameObject::GetComponent() const
{
	static_assert(std::is_base_of<Component, T>(), "This class is not a component.");

	for (const auto& component : m_pComponents)
	{
		if (const auto& comp = dynamic_pointer_cast<T>(component))
		{
			return comp;
		}
	}

	return nullptr;
}