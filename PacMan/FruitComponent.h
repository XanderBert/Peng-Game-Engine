#pragma once
#include "Component.h"

class FruitComponent final : public Component
{
public:
	FruitComponent(GameObject* pParent);
	~FruitComponent() override = default;
	FruitComponent(const FruitComponent& other) = delete;
	FruitComponent(FruitComponent&& other) noexcept = delete;
	FruitComponent& operator=(const FruitComponent& other) = delete;
	FruitComponent& operator=(FruitComponent&& other) noexcept = delete;

	void Update() override {}
	void Render() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void OnCollision(GameObject*, bool, bool) override;

};
