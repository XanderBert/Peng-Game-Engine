#pragma once
#include <memory>
#include <set>
#include <string>
#include <vector>

class Component;
class Scene;
class BoxCollider;

class GameObject final
{
public:
	GameObject();
	~GameObject();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	//Called each frame
	void Update();

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float fixedTimeMStep);

	//Called after the Update()c
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate();

	//Called each frame
	void Render() const;


	//
	//Components
	template <typename T> std::shared_ptr <T> AddComponent();
	template <typename T> void RemoveComponent() const;
	template <typename T> std::shared_ptr<T> GetComponent() const;

	std::vector<std::shared_ptr<Component>> m_pComponents{};

	//
	//SceneGraph
	void SetParent(GameObject* pParent, bool keepWorldPosition);
	int GetChildCount() const;

	GameObject* GetParent() const;
	GameObject* GetChildAt(int index) const;
	std::vector<GameObject*> GetChildren() const;

	//
	//Deletion
	bool CanBeDeleted()const
	{
		return m_CanBeDeleted;
	}

	//Will delete the object in the late update
	void MarkForDeletion();

	//
	//Collision
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger);
	std::set<GameObject*> GetCollidingObjects() const;

	Scene* GetScene() const { return m_pScene; }
	void SetScene(Scene* pScene) { m_pScene = pScene; }

protected:
	GameObject* m_pParent{};
	bool m_CanBeDeleted{ false };
	std::vector<GameObject*> m_pChildren{};
	Scene* m_pScene{};
	void AddToChildVector(GameObject* pChild);
	void RemoveFromChildren(GameObject* pParent) const;

private:
	void RemoveComponents();
	//Just accesses the component and marks it for deletion
	void MarkComponentForDeletionUtility(Component* component) const;

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
void GameObject::RemoveComponent() const
{
	static_assert(std::is_base_of<Component, T>(), "This class is not a component.");

	for (const auto& component : m_pComponents)
	{
		if (const auto& comp = dynamic_pointer_cast<T>(component))
		{
			//Just accesses the component and marks it for deletion
			//This is done in the cpp because the template really does not like it when access the component here.
			MarkComponentForDeletionUtility(comp.get());
		}
	}
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