#pragma once
#include <string>
#include <vector>
class GameObject;
class Scene;

class WallManager final
{
public:
	WallManager() = default;
	~WallManager() = default;

	WallManager(const WallManager& other) = delete;
	WallManager(WallManager&& other) noexcept = delete;
	WallManager& operator=(const WallManager& other) = delete;
	WallManager& operator=(WallManager&& other) noexcept = delete;


	//void InitWalls();
	void AddWall(const std::string& pictureName);
	void AddWallsToScene(Scene& scene);

private:
	std::vector<GameObject*> m_pWalls;
};

