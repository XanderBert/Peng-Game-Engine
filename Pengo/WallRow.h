#pragma once
#include <glm/vec2.hpp>

#include "Wall.h"

class WallRow final : public GameObject
{
public:
	WallRow(glm::vec2 startingPos, glm::vec2 size);
	~WallRow() = default;

	WallRow(const WallRow& other) = delete;
	WallRow(WallRow&& other) noexcept = delete;
	WallRow& operator=(const WallRow& other) = delete;
	WallRow& operator=(WallRow&& other) noexcept = delete;

private:
	glm::vec2 m_StartingPos{};
	glm::vec2 m_Size{};
	glm::vec2 m_WallSize{};
};
