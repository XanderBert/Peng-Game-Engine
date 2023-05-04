#pragma once
#include "Component.h"
class TransformEx : public Component
{
public:
	TransformEx(GameObject* owner);
	virtual ~TransformEx() override;

	TransformEx(const TransformEx& other) = delete;
	TransformEx(TransformEx&& other)noexcept = delete;
	TransformEx& operator=(const TransformEx& other) = delete;
	TransformEx& operator=(TransformEx&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;
private:
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

