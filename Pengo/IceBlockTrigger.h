#pragma once
#include <glm/vec2.hpp>

#include "GameObject.h"
#include "IceBlock.h"

class IceBlockTrigger final : public GameObject
{
public:
	IceBlockTrigger(IceBlock* pParent);
	virtual ~IceBlockTrigger() override;

	IceBlockTrigger(const IceBlockTrigger& other) = delete;
	IceBlockTrigger(IceBlockTrigger&& other) noexcept = delete;
	IceBlockTrigger& operator=(const IceBlockTrigger& other) = delete;
	IceBlockTrigger& operator=(IceBlockTrigger&& other) noexcept = delete;

	virtual void Update() override;
	virtual void OnCollision(GameObject* other) override;
private:
	//This is somewhat bigger then the sprite
	//The sprite collider will handle the stopping and this collider will handle the attack
	const glm::vec2 m_CollisionSize{ 22,22 };
};
