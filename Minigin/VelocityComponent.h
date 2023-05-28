#pragma once
#include "Component.h"

class VelocityComponent final : public Component
{
public:
	VelocityComponent(GameObject* pOwner);
	virtual ~VelocityComponent() override = default;

	VelocityComponent(const VelocityComponent& other) = delete;
	VelocityComponent(VelocityComponent&& other)noexcept = delete;
	VelocityComponent& operator=(const VelocityComponent& other) = delete;
	VelocityComponent& operator=(VelocityComponent&& other)noexcept = delete;

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

	void SetVelocity(float velocity);
	float GetVelocity() const;
private:
	float m_Velocity{ 0.f };
};
