#pragma once
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
	virtual void FixedUpdate(float fixedTimeMStep) = 0;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() = 0;

	//Called each frame
	virtual void Render() = 0;

	void MarkForDeletion();
	bool CanBeDeleted() const;

	GameObject* GetGameObject() const;

protected:
	bool m_WillBeDeleted{ false };
	GameObject* m_pOwner{ nullptr };
private:
	void SetGameObject(GameObject* owner);
};