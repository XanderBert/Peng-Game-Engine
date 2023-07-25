#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "TriggerComponent.h"

class IntersectionTile final
{
public:
	IntersectionTile(const glm::vec2& position, const std::vector<glm::vec2>& possibleDirection);
	~IntersectionTile() = default;

	IntersectionTile(const IntersectionTile& other) = delete;
	IntersectionTile(IntersectionTile&& other) = delete;
	IntersectionTile& operator=(const IntersectionTile& other) = delete;
	IntersectionTile& operator=(IntersectionTile&& other) = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }
private:
	GameObject* m_pGameObject;
};


