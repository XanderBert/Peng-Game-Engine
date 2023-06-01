#pragma once
#include "Component.h"
class CountdownComponent final : public Component
{
public:
	CountdownComponent(GameObject* owner);
	~CountdownComponent() override;

	CountdownComponent(const CountdownComponent& other) = delete;
	CountdownComponent(CountdownComponent&& other) noexcept = delete;
	CountdownComponent& operator=(const CountdownComponent& other) = delete;
	CountdownComponent& operator=(CountdownComponent&& other) = delete;

	void Update() override;
	void FixedUpdate(float fixedTimeMStep) override;
	void LateUpdate() override;
	void Render() override;

	void SetTime(float time) { m_Time = time; m_InitTime = time; }
	float GetTime() const { return m_Time; }
	bool IsTimeUp() const { return m_Time <= 0.f; }

	void AddTime(float time) { m_Time += time; }
	void SubtractTime(float time) { m_Time -= time; }

	void ResetTime() { m_Time = m_InitTime; }
	void Play() { m_Play = true; }
	void Pause() { m_Play = false; }

private:
	bool m_Play{ false };
	float m_Time{};
	float m_InitTime{};
};
