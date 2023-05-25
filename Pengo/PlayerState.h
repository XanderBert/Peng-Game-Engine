#pragma once
#include "InputManager.h"
#include "ServiceLocator.h"

class PlayerState
{
public:
	PlayerState(GameActor* object) : m_pActor{ object } {}
	virtual ~PlayerState() = default;
	virtual PlayerState* HandleInput() = 0;
	virtual void Update() = 0;
	virtual void OnCollision() = 0;
private:
	virtual void OnEnter() = 0;
protected:
	GameActor* m_pActor{};
};

class AttackingState final : public PlayerState
{
public:
	AttackingState(GameActor* object) : PlayerState{ object } { OnEnter(); }
	~AttackingState() override = default;
	virtual PlayerState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision() override;
private:
	virtual void OnEnter() override;
private:
	float m_TimeUntilMoveState{ 0.3f };
};

class MovingState final : public PlayerState
{
public:
	MovingState(GameActor* object) : PlayerState{ object } { OnEnter(); }
	~MovingState() override = default;
	virtual PlayerState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision() override;
private:
	virtual void OnEnter() override;
};