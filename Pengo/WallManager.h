#pragma once
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "Wall.h"


class WallManager final : public GameObject
{
public:
	WallManager();
	virtual ~WallManager() override;

	WallManager(const WallManager& other) = delete;
	WallManager(WallManager&& other)noexcept = delete;
	WallManager& operator=(const WallManager& other) = delete;
	WallManager& operator=(WallManager&& other)noexcept = delete;
private:
	std::vector<glm::vec2> m_WallCoordinates{};
	std::vector<Wall*> m_Walls{};

	void CalculateWallRows();
};
