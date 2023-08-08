#pragma once
#include "Component.h"

class IntersectionComponent final : public Component
{
public:
	IntersectionComponent(GameObject* pParent) : Component(pParent) {}
	~IntersectionComponent() override = default;

	IntersectionComponent(const IntersectionComponent& other) = delete;
	IntersectionComponent(IntersectionComponent&& other) = delete;
	IntersectionComponent& operator=(const IntersectionComponent& other) = delete;
	IntersectionComponent& operator=(IntersectionComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	std::vector<glm::vec2> GetDirections() const { return m_Directions; }
	void AddDirection(const glm::vec2& direction) { m_Directions.push_back(direction); }
	void SetDirections(const std::vector<glm::vec2>& directions)
	{
		m_Directions.clear();
		m_Directions.reserve(directions.size());
		m_Directions = directions;
	}

private:
	std::vector<glm::vec2> m_Directions;
};