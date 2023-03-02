#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class Transform final : public Component
{
public:
	Transform();
	~Transform();

	Transform(const Transform& other) = delete;
	Transform(Transform&& other) = delete;
	Transform& operator=(const Transform& other) = delete;
	Transform& operator=(Transform&& other) = delete;


	//Called each frame
	void Update(float deltaT);

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float fixedTimeStep);

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate(float deltaT);

	//Called each frame
	void Render() const;

	const glm::vec2& GetPosition() const;
	void SetPosition(const glm::vec2& newPosition);
private:
	glm::vec2 m_position{};
};

