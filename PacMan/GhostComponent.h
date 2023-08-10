#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
#include "PacManState.h"


class GhostComponent final : public Component
{
public:
	GhostComponent(GameObject* pParent);
	~GhostComponent() override;

	GhostComponent(const GhostComponent& other) = delete;
	GhostComponent(GhostComponent&& other) = delete;
	GhostComponent& operator=(const GhostComponent& other) = delete;
	GhostComponent& operator=(GhostComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override;

	//Direction
	void ChangeToRandomDirection() const;
	glm::vec2 GetDirectionOfVector(const std::vector<glm::vec2>& possibleDirections, const glm::vec2& target) const;
	glm::vec2 CalculateDirection(const glm::vec2& target) const;

	//PacMan
	void StorePacMan() const;

	//Texture
	std::string GetTexturePath() const;
	void InitScaredSprites();
	void InitChaseAndScatterSprites();

	//State
	void SetupStates();
	State* GetRandomPossibleState() const;

	//GhostNumber
	int GetGhostNumber() { return m_GhostNumber; }

	//Position
	glm::vec2 GetStartPosition() const { return m_SpawnPosition; }

	//target
	void SetTarget(const glm::vec2& target) { m_Target = target; }

private:
	inline static int m_StatGhostNumber{};
	int m_GhostNumber{};
	std::string m_TexturePath{};
	glm::vec2 m_SpawnPosition{ 104,100 };
	void SetupTexture();

	glm::vec2 m_Target{};
};
