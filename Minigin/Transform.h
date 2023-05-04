#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class Transform final : public Component
{
public:
	Transform(GameObject* owner);
	~Transform() override;

	Transform(const Transform& other) = delete;
	Transform(Transform&& other) = delete;
	Transform& operator=(const Transform& other) = delete;
	Transform& operator=(Transform&& other) = delete;


	//Called each frame
	void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate() override;

	//Called each frame
	void Render() override;

	//
	//Position
	void SetLocalPosition(const glm::vec2& position);
	glm::vec2 GetLocalPosition();

	void SetWorldPosition(const glm::vec2& position);
	glm::vec2 GetWorldPosition();
	void SetPositionDirty();

	//
	//Rotation
	void SetLocalRotation(const glm::vec2& angle);
	glm::vec2 GetLocalRotation() const;

	void SetWorldRotation(const glm::vec2& angle);
	glm::vec2 GetWorldRotation() const;

	//
	//Scale
	void SetLocalScale(const glm::vec2& scale);
	glm::vec2 GetLocalScale() const;

	void SetWorldScale(const glm::vec2 scale);
	glm::vec2 GetWorldScale() const;

	bool IsPositionDirty() const { return m_IsPositionDirty; }

private:
	glm::mat3x3 m_TranformMatrixWorld = glm::mat3x3{ {1, 0 ,0},{0, 1, 0},{0, 0, 1} };

	bool m_IsPositionDirty{ false };
	void UpdateWorldPosition();
	void _UpdateWorldPosition(Transform* parentTransComponent);
};