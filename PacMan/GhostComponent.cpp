#include "GhostComponent.h"
#include "glm/vec2.hpp"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureRenderer.h"

GhostComponent::GhostComponent(GameObject* pParent) : Component(pParent)
{
    const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
    
    int ghosts = 0;

    for(const auto gameObject : objects)
    {
	    if(gameObject->GetComponent<GhostComponent>())
	    {
		    ++ghosts;
	    }
    }
    
    switch (ghosts)
    {
        case 1:
			m_pOwner->GetComponent<TextureRenderer>()->SetTexture("GhostRed.png");
			break;
		case 2:
            m_pOwner->GetComponent<TextureRenderer>()->SetTexture("GhostBlue.png");
			break;

        case 3: 
            m_pOwner->GetComponent<TextureRenderer>()->SetTexture("GhostPink.png");
            break;
        case 0: 
            m_pOwner->GetComponent<TextureRenderer>()->SetTexture("GhostOrange.png");
            break;
    }
}


void GhostComponent::ChangeToRandomDirection()
{
    if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
    {
        const glm::vec2 oldDirection{ directionComponent->GetDirection() };

        auto newDirection = oldDirection;

        // Generate a new direction until it is different from the old direction and not opposite (180-degree turn)
        while (newDirection == oldDirection || newDirection == -oldDirection)
        {
            // Generate a random integer between 1 and 3 (to avoid full 180-degree turns)
            const int numQuarterTurns = 1 + std::rand() % 3;

            // Perform the quarter turns
            for (int i = 0; i < numQuarterTurns; ++i)
            {
                const float temp = newDirection.x;
                newDirection.x = -newDirection.y;
                newDirection.y = temp;
            }
        }

       ChangeDirection(newDirection);
    }
}

void GhostComponent::ChangeDirection(const glm::vec2& /*direction*/)
{
   

}
