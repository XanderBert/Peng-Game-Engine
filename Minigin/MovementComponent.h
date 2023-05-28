#pragma once
#include "Component.h"

class MovementComponent final : public Component
{
public:
	MovementComponent();
	virtual ~MovementComponent() override;

	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) noexcept = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) noexcept = delete;


private:
	float m_Velocity{ 0 };
	glm::vec2 Direction{ 0,0 };
};
