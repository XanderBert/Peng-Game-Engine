#pragma once
#include "Component.h"
#include "glm/vec2.hpp"

class DirectionComponent final : public Component
{
public:
	DirectionComponent(GameObject* owner);
	virtual ~DirectionComponent() override;

	DirectionComponent(const DirectionComponent& other) = delete;
	DirectionComponent(DirectionComponent&& other)noexcept = delete;
	DirectionComponent& operator=(const DirectionComponent& other) = delete;
	DirectionComponent& operator=(DirectionComponent&& other)noexcept = delete;

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

	void SetDirection(const glm::vec2& direction);
	void SetDirectionX(float x);
	void SetDirectionY(float y);

	glm::vec2 GetDirection() const;
	glm::vec2 GetPreviousDirection() const;
private:
	glm::vec2 m_Direction{ 0.f,0.f };
	glm::vec2 m_PreviousDirection{ 0.f,0.f };
};
