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


	void ChangeToRandomDirection() const;
	
	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	std::string GetTexturePath() const;
	void InitScaredSprites();
	void InitChaseAndScatterSprites();

private:
	std::string m_TexturePath{};

};

