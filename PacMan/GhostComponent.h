#pragma once
#include <glm/vec2.hpp>

#include "Component.h"


class GhostComponent final : public Component
{
public:
	GhostComponent(GameObject* pParent);
	~GhostComponent() override = default;

	GhostComponent(const GhostComponent& other) = delete;
	GhostComponent(GhostComponent&& other) = delete;
	GhostComponent& operator=(const GhostComponent& other) = delete;
	GhostComponent& operator=(GhostComponent&& other) = delete;




	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	void SetupTextureAndState();

	void ChangeToRandomDirection() const;
	glm::vec2 GetDirectionOfVector(const std::vector<glm::vec2>& possibleDirections, const glm::vec2& target) const;

	glm::vec2 CalculateDirection(const glm::vec2& target) const;
	void StorePacMan() const;

	std::string GetTexturePath() const;
	void InitScaredSprites();
	void InitChaseAndScatterSprites();

private:
	int m_GhostNumber{};
	std::string m_TexturePath{};

};

