#pragma once
#include "Component.h"

class WallComponent final : public Component
{
public:
	WallComponent(GameObject* pParent) : Component(pParent) {}
	~WallComponent() override = default;

	WallComponent(const WallComponent& other) = delete;
	WallComponent(WallComponent&& other) = delete;
	WallComponent& operator=(const WallComponent& other) = delete;
	WallComponent& operator=(WallComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}
};