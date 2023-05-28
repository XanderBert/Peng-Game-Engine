#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <glm/vec2.hpp>
class Component;
class BoxCollider;

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
	virtual void FixedUpdate(float fixedTimeMStep);

	//Called after the Update()c
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate();

	//Called each frame
	virtual void Render() const;


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
	bool CanBeDeleted()const { return m_CanBeDeleted; }

	//Will delete the object in the late update
	void MarkForDeletion();

	//
	//Collision
	virtual void OnCollision(GameObject* /*other*/) {}


	std::vector<GameObject*> GetCollidingObjects() const;


	//Needs to be moved to a component
	void SetDirection(const glm::vec2& direction) { m_Direction = direction; }
	glm::vec2 GetDirection() const { return  m_Direction; }
	void SetDirectionX(const float x) { m_Direction.x = x; }
	void SetDirectionY(const float y) { m_Direction.y = y; }

	//Needs to be moved to a component
	float GetVelocity() const { return  m_Velocity; }
	void SetVelocity(const float velocity) { m_Velocity = velocity; }



	//Needs to be moved to a component
	bool GetUsesController() const { return m_UsesController; }
	//This can range between 0 & 4
	void SetControllerIndex(int index);
	int GetControllerIndex() const { return m_ControllerID; }

protected:
	bool m_CanBeDeleted{ false };
	float m_Velocity{ 50.f };
	glm::vec2 m_Direction{};
	bool m_UsesController{ false };
	int m_ControllerID{};

	GameObject* m_pParent{};

	std::vector<GameObject*> m_pChildren{};
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
			//This is done in the cpp because the template really does not like it when acces the component here.
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