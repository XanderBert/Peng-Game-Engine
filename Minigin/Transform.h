#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class Transform final : public Component
{
public:
	Transform(GameObject* owner);
	~Transform();

	Transform(const Transform& other) = delete;
	Transform(Transform&& other) = delete;
	Transform& operator=(const Transform& other) = delete;
	Transform& operator=(Transform&& other) = delete;


	//Called each frame
	void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate() override;

	//Called each frame
	void Render() const override;

	//
	//Position
	void SetLocalPosition(const glm::vec2& position);
	glm::vec2 GetLocalPosition() const;

	void SetWorldPosition(const glm::vec2& position);
	glm::vec2 GetWorldPosition(GameObject* parent);
	void SetPositionDirty();

private:
	//Todo this can become a matrix and do rotation scale and transform
	glm::vec2 m_LocalPosition{};
	glm::vec2 m_WorldPosition{};

	bool m_IsPositionDirty{ false };
	void UpdateWorldPosition(GameObject* parent);
};

