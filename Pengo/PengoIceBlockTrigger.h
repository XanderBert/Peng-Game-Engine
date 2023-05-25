#pragma once
#include <glm/vec2.hpp>
#include "GameObject.h"

class PengoIceBlockTrigger final : public GameObject
{
public:
	PengoIceBlockTrigger(GameObject* pParent);
	virtual ~PengoIceBlockTrigger() override;

	PengoIceBlockTrigger(const PengoIceBlockTrigger& other) = delete;
	PengoIceBlockTrigger(PengoIceBlockTrigger&& other) noexcept = delete;
	PengoIceBlockTrigger& operator=(const PengoIceBlockTrigger& other) = delete;
	PengoIceBlockTrigger& operator=(PengoIceBlockTrigger&& other) noexcept = delete;


	virtual void Update() override;
	virtual void OnCollision(GameObject* other) override;
private:
	const float m_OffsetMultiplier{ 10.f };
	const glm::vec2 m_Offset{ 5,5 };
	const glm::vec2 m_CollisionSize{ 5,5 };
};
