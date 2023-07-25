#pragma once
#include "Component.h"

class PowerUpComponent final : public Component
{
public:
	PowerUpComponent(GameObject* pParent) : Component(pParent) {}
	~PowerUpComponent() override = default;

	PowerUpComponent(const PowerUpComponent& other) = delete;
	PowerUpComponent(PowerUpComponent&& other) = delete;
	PowerUpComponent& operator=(const PowerUpComponent& other) = delete;
	PowerUpComponent& operator=(PowerUpComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}
};