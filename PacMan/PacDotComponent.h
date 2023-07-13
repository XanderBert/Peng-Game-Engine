#pragma once
#include "Component.h"

class PacDotComponent final : public Component
{
public:
	PacDotComponent(GameObject* pParent) : Component(pParent) {}
	~PacDotComponent() override = default;

	PacDotComponent(const PacDotComponent& other) = delete;
	PacDotComponent(PacDotComponent&& other) = delete;
	PacDotComponent& operator=(const PacDotComponent& other) = delete;
	PacDotComponent& operator=(PacDotComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float fixedTimeMStep) override {}
	void LateUpdate() override {}
	void Render() override {}
};