#pragma once
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "PacManState.h"


class ChaseState final : public State
{
public:
	ChaseState(GameObject* object);
	~ChaseState() override = default;

	ChaseState(const ChaseState& other) = delete;
	ChaseState(ChaseState&& other) = delete;
	ChaseState& operator=(const ChaseState& other) = delete;
	ChaseState& operator=(ChaseState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	glm::vec2 m_Target{};
	void OnEnter() override;


};

class ScatterState final : public State
{
public:
	ScatterState(GameObject* object);
	~ScatterState() override = default;

	ScatterState(const ScatterState& other) = delete;
	ScatterState(ScatterState&& other) = delete;
	ScatterState& operator=(const ScatterState& other) = delete;
	ScatterState& operator=(ScatterState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	void OnEnter() override;
};

class FrightenedState final : public State
{
public:
	FrightenedState(GameObject* object);
	~FrightenedState() override = default;

	FrightenedState(const FrightenedState& other) = delete;
	FrightenedState(FrightenedState&& other) = delete;
	FrightenedState& operator=(const FrightenedState& other) = delete;
	FrightenedState& operator=(FrightenedState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	void OnEnter() override;

	bool m_wasDirectionChanged = false;
	float m_directionChangeTime = 0.0f;
	glm::vec2 m_previousDirection = glm::vec2(0.0f);
};


class CorneringState final : public State
{
public:
	CorneringState(GameObject* object);
	~CorneringState() override = default;

	CorneringState(const CorneringState& other) = delete;
	CorneringState(CorneringState&& other) = delete;
	CorneringState& operator=(const CorneringState& other) = delete;
	CorneringState& operator=(CorneringState&& other) = delete;

	State* HandleInput() override;
	void Update() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

private:
	glm::vec2 m_Target{};
	void OnEnter() override;
};


