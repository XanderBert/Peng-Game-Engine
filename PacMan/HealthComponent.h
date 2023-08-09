#pragma once
#include "Component.h"

class HealthComponent final : public Component
{
public:
	HealthComponent(GameObject* pParent) : Component(pParent) {}
	~HealthComponent() override = default;

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	void TakeDamage(const int damage)
	{
		m_Health -= damage;
	}
	int GetHealth() const { return m_Health; }
private:
	int m_Health{ 3 };
};