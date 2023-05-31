#pragma once
#include "GameObject.h"

class WallManager final
{
public:
	WallManager();
	~WallManager() = default;

	WallManager(const WallManager& other) = delete;
	WallManager(WallManager&& other) = delete;
	WallManager& operator=(const WallManager& other) = delete;
	WallManager& operator=(WallManager&& other) = delete;

	std::vector<GameObject*> GetHorizontalWalls() const { return m_pHorizontalWalls; }
	std::vector<GameObject*> GetVerticalWalls() const { return m_pVerticalWalls; }

private:
	std::vector<GameObject*>m_pHorizontalWalls{};
	std::vector<GameObject*>m_pVerticalWalls{};

	glm::vec2 m_HorizontalWallSize{ 224,8 };
	glm::vec2 m_VerticalWallSize{ 8,256 };

	int m_WallOffset{ 50 };

};
