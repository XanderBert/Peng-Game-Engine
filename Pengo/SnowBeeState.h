#pragma once
#include "PlayerState.h"

class SnowBeeState : public PlayerState
{
public:
	SnowBeeState(GameObject* object) : PlayerState(object) {};
	virtual ~SnowBeeState() override = default;

	virtual SnowBeeState* HandleInput() override;
	virtual void Update() override = 0;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
protected:
	void ChangeMovement();

	bool m_IsHit{};
	bool m_IsConcussed{};
	bool m_GoInAttackState{};
	//Multiplies the the direction of the previous location to prevent tunneling
	float m_TunnelingMultiplier{ 3.f };

private:
	virtual void OnEnter() override = 0;

};

//
//Spawning
class SnowBeeSpawningState final : public SnowBeeState
{
public:
	SnowBeeSpawningState(GameObject* object) : SnowBeeState(object) { OnEnter(); }
	virtual ~SnowBeeSpawningState() override = default;

	virtual SnowBeeState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	void OnEnter() override;
	float m_TimeUntilMoving{ 1.5f };
	bool m_GoInMovingState{};
};

//
//Moving
class SnowBeeMovingState final : public SnowBeeState
{
public:
	SnowBeeMovingState(GameObject* object) : SnowBeeState(object) { OnEnter(); }
	virtual ~SnowBeeMovingState() override = default;

	virtual SnowBeeState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	void OnEnter() override;
	float m_TimeUntilAttack{ };
	float m_TimeUntilMoveChange{};

};


//
//Attacking
class SnowbeeAttackingState final : public SnowBeeState
{
public:
	SnowbeeAttackingState(GameObject* object) : SnowBeeState(object) { OnEnter(); }
	virtual ~SnowbeeAttackingState() override = default;

	virtual SnowBeeState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	void OnEnter() override;
	float m_TimeUntilMoving{};
	bool m_GoInMovingState{};
};

//
//Dying
class SnowBeeDyingState final : public SnowBeeState
{
public:
	SnowBeeDyingState(GameObject* object) : SnowBeeState(object) { OnEnter(); }
	virtual ~SnowBeeDyingState() override = default;

	virtual SnowBeeState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	void OnEnter() override;
	float m_AnimationPlayTime{ 1.5f };

};

//
//Concussed
class SnowBeeConcussedState final : public SnowBeeState
{
public:
	SnowBeeConcussedState(GameObject* object) : SnowBeeState(object) { OnEnter(); }
	virtual ~SnowBeeConcussedState() override = default;

	virtual SnowBeeState* HandleInput() override;
	virtual void Update() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
private:
	void OnEnter() override;
	float m_ConcussedTime{ 5.f };
	bool m_GoInDyingState{};
};