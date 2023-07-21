#pragma once
#include "GameObject.h"
#include "PacManState.h"


class GhostMoveState final : public State
{
public:
	GhostMoveState(GameObject* object);
	~GhostMoveState() override = default;

	GhostMoveState(const GhostMoveState& other) = delete;
	GhostMoveState(GhostMoveState&& other) = delete;
	GhostMoveState& operator=(const GhostMoveState& other) = delete;
	GhostMoveState& operator=(GhostMoveState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	void OnEnter() override;
};

class GhostConcusedState final : public State
{
public:
	GhostConcusedState(GameObject* object);
	~GhostConcusedState() override = default;

	GhostConcusedState(const GhostConcusedState& other) = delete;
	GhostConcusedState(GhostConcusedState&& other) = delete;
	GhostConcusedState& operator=(const GhostConcusedState& other) = delete;
	GhostConcusedState& operator=(GhostConcusedState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	void OnEnter() override;
};