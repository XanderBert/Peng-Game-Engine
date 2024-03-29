﻿#pragma once
#include "PlayerState.h"


class PengoState : public PlayerState
{
public:
	PengoState(GameObject* object) : PlayerState{ object } {}
	virtual ~PengoState() override = default;

	virtual PengoState* HandleInput() override = 0;
	virtual void Update() override = 0;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override = 0;
protected:
	bool IsHit(GameObject* other, bool isTrigger, bool isSenderTrigger);
	bool m_IsHit{ false };
private:
	virtual void OnEnter() override = 0;

};

class IdleState final : public PengoState
{
public:
	IdleState(GameObject* object) : PengoState{ object } { OnEnter(); }
	~IdleState() override = default;

	virtual PengoState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	virtual void OnEnter() override;
};

class AttackingState final : public PengoState
{
public:
	AttackingState(GameObject* object) : PengoState{ object } { OnEnter(); }
	~AttackingState() override = default;
	virtual PengoState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	virtual void OnEnter() override;
	float m_TimeUntilIdle{ 0.3f };
	bool m_MovedIceBlock{ false };
};

class MovingState final : public PengoState
{
public:
	MovingState(GameObject* object) : PengoState{ object } { OnEnter(); }
	~MovingState() override = default;
	virtual PengoState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	virtual void OnEnter() override;
	float m_TimeUntilIdle{ 0.5f };
};


class DyingState final : public PengoState
{
public:
	DyingState(GameObject* object) : PengoState{ object } { OnEnter(); }
	~DyingState() override = default;
	virtual PengoState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	virtual void OnEnter() override;
	int m_Animations{ };
	float m_AnimationPlayTime{ 1.5f };
};