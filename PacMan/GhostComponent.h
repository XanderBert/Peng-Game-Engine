#pragma once
#include <iostream>
#include <glm/vec2.hpp>
#include "Component.h"
#include "DirectionComponent.h"
#include "TimeM.h"

class GhostComponent final : public Component
{
public:
	GhostComponent(GameObject* pParent);
	~GhostComponent() override = default;

	GhostComponent(const GhostComponent& other) = delete;
	GhostComponent(GhostComponent&& other) = delete;
	GhostComponent& operator=(const GhostComponent& other) = delete;
	GhostComponent& operator=(GhostComponent&& other) = delete;


	void ChangeToRandomDirection();
	void ChangeDirection(const glm::vec2& direction);

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

private:
	std::vector<std::pair<glm::vec2, float>> m_DirectionChanges;

};

