#pragma once
#include <glm/vec2.hpp>

#include "GameObject.h"

class SnowBee final : public GameObject
{
public:
	SnowBee();
	~SnowBee() override = default;

	SnowBee(const SnowBee& other) = delete;
	SnowBee(SnowBee&& other)noexcept = delete;
	SnowBee& operator=(const SnowBee& other) = delete;
	SnowBee& operator=(SnowBee&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(GameObject* other) override;
private:
	glm::vec2 m_Direction{ -1,0 };
	float m_velocity{ 10 };

	void ChangeMovement();
	void Move() const;
	void StopMovement() const;
};
