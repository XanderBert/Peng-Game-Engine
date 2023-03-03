#pragma once
#include <memory>
#include <vector>

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

	template <typename T> std::shared_ptr <T> AddComponent();
	template <typename T> std::shared_ptr<T> GetComponent() const;

	std::vector<std::shared_ptr<Component>> m_pComponents{};

private:
	void RemoveComponents();
};

template<typename T>
std::shared_ptr <T> GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>(), "This class is not a component.");

	auto pComponent = std::make_shared<T>();

	pComponent->SetGameObject(this);

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