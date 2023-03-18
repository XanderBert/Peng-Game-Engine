#pragma once
#include <memory>
#include "GameObject.h"

class Component
{
public:
	Component(GameObject* owner);
	virtual ~Component();

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	//Called each frame
	virtual void Update() = 0;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep) = 0;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() = 0;

	//Called each frame
	virtual void Render() = 0;

	void MarkForDeletion();
	bool CanBeDeleted() const;

	template <typename T>
	std::shared_ptr<T> GetComponent() const;

protected:
	bool m_WillBeDeleted{ false };
	GameObject* m_pOwner{ nullptr };
private:
	void SetGameObject(GameObject* owner);
};

//return nullptr if the component has not been found
template <typename T>
std::shared_ptr<T> Component::GetComponent() const
{
	if (m_pOwner)
	{
		return m_pOwner->GetComponent<T>();
	}
	return nullptr;
}