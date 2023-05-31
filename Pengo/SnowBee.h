#pragma once
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "IceBlock.h"
#include "playerState.h"

class SnowBee final : public GameObject
{
public:
	SnowBee();
	virtual ~SnowBee() override;

	SnowBee(const SnowBee& other) = delete;
	SnowBee(SnowBee&& other)noexcept = delete;
	SnowBee& operator=(const SnowBee& other) = delete;
	SnowBee& operator=(SnowBee&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(GameObject* other, bool isTrigger) override;

	float GetVelocity() const { return m_velocity; }

	//Store Object component
	GameObject* GetHittedIceBlock() const { return m_pHittedIceBlock; }
	void SetHittedIceBlock(GameObject* pIceBlock) { m_pHittedIceBlock = pIceBlock; }

private:

	float m_velocity{ 10 };
	glm::vec2 m_SpriteSize{ 16,16 };
	GameObject* m_pHittedIceBlock{};
	PlayerState* m_pState{};


	void UpdateState();
};
