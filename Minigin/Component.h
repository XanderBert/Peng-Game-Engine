#pragma once
class Component
{
public:
	Component();
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
private:
};

