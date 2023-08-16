#pragma once
#include "GameObject.h"

class State
{
public:
	State(GameObject* object) :m_pActor(object) {};
	virtual ~State() = default;


	State(const State& other) = delete;
	State(State&& other) = delete;
	State& operator=(const State& other) = delete;
	State& operator=(State&& other) = delete;

	virtual State* HandleInput() = 0;
	virtual void Update() = 0;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) = 0;
	virtual void OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger) = 0;

protected:
	GameObject* m_pActor{};

private:
	virtual void OnEnter() = 0;
};



class PacManMoveState final : public State
{
public:
	PacManMoveState(GameObject* object);
	~PacManMoveState() override = default;

	PacManMoveState(const PacManMoveState& other) = delete;
	PacManMoveState(PacManMoveState&& other) = delete;
	PacManMoveState& operator=(const PacManMoveState& other) = delete;
	PacManMoveState& operator=(PacManMoveState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
	void OnCollisionEnter(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/) override {}

private:
	void OnEnter() override;
};

class PacManIdleState final : public State
{
public:
	PacManIdleState(GameObject* object);
	~PacManIdleState() override = default;

	PacManIdleState(const PacManIdleState& other) = delete;
	PacManIdleState(PacManIdleState&& other) = delete;
	PacManIdleState& operator=(const PacManIdleState& other) = delete;
	PacManIdleState& operator=(PacManIdleState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
	void OnCollisionEnter(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/) override {}

private:
	void OnEnter() override;
};

class PacManFrightenedState final : public State
{
public:
	PacManFrightenedState(GameObject* object);
	~PacManFrightenedState() override = default;

	PacManFrightenedState(const PacManFrightenedState& other) = delete;
	PacManFrightenedState(PacManFrightenedState&& other) = delete;
	PacManFrightenedState& operator=(const PacManFrightenedState& other) = delete;
	PacManFrightenedState& operator=(PacManFrightenedState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;
	void OnCollisionEnter(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	void OnEnter() override;
};