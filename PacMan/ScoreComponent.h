#pragma once
#include "Component.h"

class ScoreComponent final : public Component
{
public:
	ScoreComponent(GameObject* pParent) : Component(pParent) {}
	~ScoreComponent() override = default;

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	void IncreaseScore(const int score) { m_Score += score; }
	int GetScore() const { return m_Score; }
private:
	int m_Score{};
};