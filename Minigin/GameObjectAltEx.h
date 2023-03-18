#pragma once
#include "Component.h"
#include "TransformEx.h"

class GameObjectAltEx : public Component
{
public:
	GameObjectAltEx(GameObject* owner);
	virtual ~GameObjectAltEx() override;

	GameObjectAltEx(const GameObjectAltEx& other) = delete;
	GameObjectAltEx(GameObjectAltEx&& other)noexcept = delete;
	GameObjectAltEx& operator=(const GameObjectAltEx& other) = delete;
	GameObjectAltEx& operator=(GameObjectAltEx&& other)noexcept = delete;

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
	TransformEx* transform;
	int ID;
};
