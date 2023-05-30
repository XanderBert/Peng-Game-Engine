#pragma once
#include "Pengo.h"
#include "PlayerState.h"


class PengoState : public PlayerState
{
public:
	PengoState(GameObject* object) : PlayerState{ object } {}
	virtual ~PengoState() override = default;

	virtual PengoState* HandleInput() override = 0;
	virtual void Update() override = 0;
	virtual void OnCollision(GameObject* other) override;
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
	virtual void OnCollision(GameObject* other) override;
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
	virtual void OnCollision(GameObject* other) override;
private:
	virtual void OnEnter() override;
	float m_TimeUntilIdle{ 0.3f };
};

class MovingState final : public PengoState
{
public:
	MovingState(GameObject* object) : PengoState{ object } { OnEnter(); }
	~MovingState() override = default;
	virtual PengoState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other) override;
private:
	virtual void OnEnter() override;
	float m_TimeUntilIdle{ 0.5f };
};