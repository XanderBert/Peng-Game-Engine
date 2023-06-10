#pragma once
#include "GameObject.h"

class DiamondBlock final : public GameObject
{
public:
	DiamondBlock();
	virtual ~DiamondBlock() override;

	DiamondBlock(const DiamondBlock& other) = delete;
	DiamondBlock(DiamondBlock&& other) noexcept = delete;
	DiamondBlock& operator=(const DiamondBlock& other) = delete;
	DiamondBlock& operator=(DiamondBlock&& other) noexcept = delete;

	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

	void SetCollidingWithOtherDiamondBlock(bool colliding) { collidingWithOtherDiamondBlock = colliding; }
	bool IsCollidingWithOtherDiamondBlock() const { return collidingWithOtherDiamondBlock; }


private:
	glm::vec2 m_SpriteSize{ 16,16 };
	glm::vec2 m_TriggerSize{ 20,20 };
	bool collidingWithOtherDiamondBlock = false;

};
