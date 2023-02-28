#pragma once

class GameObject;
class Component
{
public:
	Component(int id);
	virtual ~Component();

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

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

	void SetId(const int id) { m_ID = id; }
	void MarkForDeletion();
	bool CanBeDeleted() const;
	void SetGameObject(GameObject* owner);
private:
	int m_ID{};
	bool m_WillBeDeleted{false};
	GameObject* m_pOwner{nullptr};
};

