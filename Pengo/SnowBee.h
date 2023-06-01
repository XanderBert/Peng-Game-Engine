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
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;


	PlayerState* GetState() const { return m_pState; }
private:

	glm::vec2 m_SpriteSize{ 16,16 };
	PlayerState* m_pState{};
	void UpdateState();
};
