#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

#include "Component.h"

class Component;
namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Called each frame
		virtual void Update([[maybe_unused]] float deltaT);

		//Called at a fixed time step
		//Used for physics & networking
		virtual void FixedUpdate([[maybe_unused]] float fixedTimeStep);

		//Called after the Update()
		//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
		virtual void LateUpdate([[maybe_unused]] float deltaT);

		//Called each frame
		virtual void Render() const;
		
		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template <typename T> T* AddComponent();
		template <typename T> T* GetComponent(int id) const;
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent(int id);

		std::vector<std::unique_ptr<Component>> m_pComponents{};

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
		int m_LastId{};
	};

	template<typename T>
	T* GameObject::AddComponent()
	{
		m_pComponents.emplace_back(std::make_unique<T>(m_LastId++));
		m_pComponents.back()->SetGameObject(*this);
		return m_pComponents.back();
	}

	template<typename T>
	T* GameObject::GetComponent(int id) const
	{
		if(id > m_pComponents.size()|| id < 0) return nullptr;

		return m_pComponents.at(id);
	}

	template<typename T>
	T* GameObject::GetComponent() const
	{
		for (const auto& component : m_pComponents)
		{
			if (dynamic_cast<T*>(component.get())) return component;
		}

		return nullptr;
	}

	template<typename T>
	void GameObject::RemoveComponent(int id)
	{	//TODO only gets removed from list not deleted
		//TODO Only delete marked for deletion components
		if (id > m_pComponents.size() || id < 0) return;
		if(m_pComponents.at(id)->CanBeDeleted())
		{
			m_pComponents.erase(m_pComponents.begin() + id);
		}
	}
}