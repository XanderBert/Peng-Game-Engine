﻿#pragma once
#include "GameActor.h"
#include "PengoIceBlockTrigger.h"
#include "PlayerState.h"

class Pengo final : public GameActor
{
public:
	Pengo();
	virtual ~Pengo() override;

	Pengo(const Pengo& other) = delete;
	Pengo(Pengo&& other)noexcept = delete;
	Pengo& operator=(const Pengo& other) = delete;
	Pengo& operator=(Pengo&& other)noexcept = delete;

	void Move(const glm::vec2& direction) override;
	void Attack() override;

	//Called each frame
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(GameObject* other) override;

	PlayerState* GetState() const { return m_pState; }
	PengoIceBlockTrigger* GetPengoIceBlockTrigger() const { return m_pIceBlockTrigger; }

private:
	PengoIceBlockTrigger* m_pIceBlockTrigger{};
	PlayerState* m_pState{};
	float m_TimeUntilCollisionForget{ 0.3f };

	void StopMovement() const;
	void UpdateState();

};
