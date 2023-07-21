#include "WallManager.h"

#include <glm/vec2.hpp>

#include "BoxCollider.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Transform.h"
#include "Scene.h"
#include "Wallcomponent.h"

void WallManager::AddWall(const std::string& pictureName)
{
	GameObject* wall = new GameObject();

    // Find the position values
    std::size_t xPosStart = pictureName.find("_") + 1;
    std::size_t xPosEnd = pictureName.find("x");
    std::size_t yPosStart = xPosEnd + 1;
    std::size_t yPosEnd = pictureName.find("_", yPosStart);

    std::string xPosition = pictureName.substr(xPosStart, xPosEnd - xPosStart);
    std::string yPosition = pictureName.substr(yPosStart, yPosEnd - yPosStart);

    // Find the size values
    std::size_t sizeXStart = yPosEnd + 1;
    std::size_t sizeXEnd = pictureName.find("x", sizeXStart);
    std::size_t sizeYStart = sizeXEnd + 1;

    std::string sizeX = pictureName.substr(sizeXStart, sizeXEnd - sizeXStart);
    std::string sizeY = pictureName.substr(sizeYStart);

    // Convert the extracted values to integers
    int x = std::stoi(xPosition);
    int y = std::stoi(yPosition);
    int width = std::stoi(sizeX);
    int height = std::stoi(sizeY);

    // Store the values in glm::vec2 variables
    glm::vec2 colliderSize(width, height);
    glm::vec2 colliderOffset(x, y);

    
    wall->GetComponent<Transform>()->SetWorldPosition(colliderOffset);

    wall->AddComponent<TextureRenderer>()->SetTexture(pictureName);
    wall->AddComponent<WallComponent>();
	

	const auto collider = wall->AddComponent<BoxCollider>();
	collider->SetColliderSize(colliderSize);
#ifdef _DEBUG
    collider->DebugRender(true);
#endif // DEBUG


	m_pWalls.emplace_back(wall);
}

void WallManager::AddWallsToScene(Scene& scene)
{
	for (const auto& wall : m_pWalls)
	{
		scene.Add(wall);
	}

    //Release the memory, otherwise walls are stored 2 times
    m_pWalls.clear();
}
