#pragma once
#include "Component.h"

class MoveComponent final : public Component
{
public:
	MoveComponent(GameObject* pOwner);
	virtual ~MoveComponent() override = default;

	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(MoveComponent&& other)noexcept = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(MoveComponent&& other)noexcept = delete;

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

	void SetCanMove(bool canMove);
	bool CanMove() const;

private:
	bool m_CanMove{ false };
	
};
