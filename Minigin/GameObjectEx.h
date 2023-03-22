#pragma once
#include "Component.h"
#include "TransformEx.h"

class GameObjectEx : public Component
{
public:
	GameObjectEx(GameObject* owner);
	virtual ~GameObjectEx() override;

	GameObjectEx(const GameObjectEx& other) = delete;
	GameObjectEx(GameObjectEx&& other)noexcept = delete;
	GameObjectEx& operator=(const GameObjectEx& other) = delete;
	GameObjectEx& operator=(GameObjectEx&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;
private:
	TransformEx transform;
	int ID;
};
