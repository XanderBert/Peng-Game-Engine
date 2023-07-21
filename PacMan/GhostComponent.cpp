#include "GhostComponent.h"

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

void GhostComponent::ChangeDirection(const glm::vec2& direction)
{
    // Check if there's any direction change within the last 0.1 seconds
    bool hasRecentDirectionChange = false;
    for (const auto& directionChange : m_DirectionChanges)
    {
        if (TimeM::GetInstance().GetElapsed() - directionChange.second <= 3.5f)
        {
            hasRecentDirectionChange = true;
            break;
        }
    }

    if (hasRecentDirectionChange && direction == -m_pOwner->GetComponent<DirectionComponent>()->GetDirection())
    {
        return;
    }

    m_pOwner->GetComponent<DirectionComponent>()->SetDirection(direction);

    std::pair newDirectionChange{ direction, TimeM::GetInstance().GetElapsed() };
    m_DirectionChanges.emplace_back(newDirectionChange);

    // Delete all direction changes that are older than 3.6 sec
    m_DirectionChanges.erase(
        std::remove_if(m_DirectionChanges.begin(), m_DirectionChanges.end(),
            [](const std::pair<glm::vec2, float>& directionChange)
            {
                return TimeM::GetInstance().GetElapsed() - directionChange.second > 3.6f;
            }),
        m_DirectionChanges.end());

}
