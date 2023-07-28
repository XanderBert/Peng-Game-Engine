#include "GhostComponent.h"
#include "glm/vec2.hpp"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteRenderer.h"
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
		case 0:
            m_TexturePath = "GhostOrange.png";
			break;
        case 1:
            m_TexturePath = "GhostRed.png";
			break;
		case 2:
            m_TexturePath = "GhostBlue.png";
			break;

        case 3: 
            m_TexturePath = "GhostPink.png";
            break;
    }

    m_pOwner->GetComponent<TextureRenderer>()->SetTexture(m_TexturePath);
}


void GhostComponent::ChangeToRandomDirection() const
{
    if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
    {
        const glm::vec2 oldDirection{ directionComponent->GetDirection() };

        auto newDirection = oldDirection;

        // Generate a new direction until it is different from the old direction and not opposite (180-degree turn)
        while (newDirection == oldDirection || glm::abs(glm::dot(newDirection, oldDirection) + 1.f) < FLT_EPSILON)
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

       directionComponent->SetDirection(newDirection);
    }
}

std::string GhostComponent::GetTexturePath() const
{
    return m_TexturePath;
}

void GhostComponent::InitScaredSprites()
{
    const auto spriteRenderer = m_pOwner->GetComponent<SpriteRenderer>();
    spriteRenderer->ResetSpriteFrames();
    spriteRenderer->SetTexture("GhostScared.png");


    const auto x = 16;
    for (size_t i{}; i < 3; ++i)
    {
        spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Down);
        spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Up);
        spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Left);
        spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Right);
    }
}

void GhostComponent::InitChaseAndScatterSprites()
{
    //If it came out of scared state
    const auto spriteRenderer = m_pOwner->GetComponent<SpriteRenderer>();
    spriteRenderer->ResetSpriteFrames();

    spriteRenderer->SetTexture(m_TexturePath);

    spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Right);
    spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Right);

    spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
    spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);

    spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
    spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);

    spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Down);
    spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Down);
    
}
