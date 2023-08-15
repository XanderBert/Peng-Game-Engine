#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
#include "DirectionComponent.h"
#include "PacManState.h"
#include "ServiceLocator.h"


class GhostComponent final : public Component
{
public:
	GhostComponent(GameObject* pParent);
	~GhostComponent() override;

	GhostComponent(const GhostComponent& other) = delete;
	GhostComponent(GhostComponent&& other) = delete;
	GhostComponent& operator=(const GhostComponent& other) = delete;
	GhostComponent& operator=(GhostComponent&& other) = delete;

	void Update() override
	{
	}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override;

	//Direction
	glm::vec2 GetRandomPossibleDirection(const std::vector<glm::vec2>& possibleDirections) const;
	glm::vec2 GetDirectionOfVector(const std::vector<glm::vec2>& possibleDirections, const glm::vec2& target) const;
	glm::vec2 CalculateDirection(const glm::vec2& target) const;

	//PacMan
	void StorePacMan() const;

	//Texture
	std::string GetTexturePath() const;
	void InitScaredSprites();
	void InitChaseAndScatterSprites();
	void InitEyesSprites();

	//State
	void SetupStates();
	State* GetRandomPossibleState() const;

	//GhostNumber
	int GetGhostNumber() { return m_GhostNumber; }

	//Position
	glm::vec2 GetStartPosition() const { return m_SpawnPosition; }
	void CenterGhost(const glm::vec2& colliderCenter, const glm::vec2& ghostCenter);

	//target
	void SetTarget(const glm::vec2& target) { m_Target = target; }

	//Cornering
	void SetCornering(bool isCornering) { m_IsCornering = isCornering; }
	bool IsCornering() const { return m_IsCornering; }



private:
	inline static int m_StatGhostNumber{};
	int m_GhostNumber{};
	std::string m_TexturePath{};
	glm::vec2 m_SpawnPosition{ 104,95 };

	bool m_IsCornering = true;
	void SetupTexture();

	glm::vec2 m_Target{};
};
