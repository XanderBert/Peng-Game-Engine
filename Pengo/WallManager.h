#include "WallManager.h"
#pragma once
#include "GameObject.h"
#include "glm/vec2.hpp"

class WallManager final : public GameObject
{
public:
	WallManager();
	~WallManager() override = default;


	WallManager(const WallManager& other) = delete;
	WallManager(WallManager&& other) = delete;
	WallManager& operator=(const WallManager& other) = delete;
	WallManager& operator=(WallManager&& other) = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() const override;

	std::vector<GameObject*> GetWalls() const { return m_pWalls; }

private:
	std::vector<GameObject*>m_pWalls{};


	glm::vec2 m_HorizontalWallSize{ 224,8 };
	glm::vec2 m_VerticalWallSize{ 8,256 };

	float m_WallOffset{ 50 };

	float m_TimeUntilMovingStateIsOver{ 3.f };

};
