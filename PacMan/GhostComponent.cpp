#include "GhostComponent.h"

#include <iostream>
#include <random>

#include "CountdownComponent.h"
#include "DirectionComponent.h"
#include "GameObjectStorage.h"
#include "GhostState.h"
#include "PacManComponent.h"
#include "Renderer.h"
#include "glm/vec2.hpp"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "StateComponent.h"
#include "TextureRenderer.h"

GhostComponent::GhostComponent(GameObject* pParent) : Component(pParent)
{
	//When going to he next level ghosts gets remade ->? So the static counter is increased
	m_StatGhostNumber = (m_StatGhostNumber % 4);
	++m_StatGhostNumber;

	m_GhostNumber = m_StatGhostNumber;

	m_pOwner->GetComponent<Transform>()->SetWorldPosition({ 77.5 + (11 * m_GhostNumber),104 });
	SetupTexture();
}

GhostComponent::~GhostComponent()
{
}


void GhostComponent::CenterGhost(const glm::vec2& colliderCenter, const glm::vec2& ghostCenter)
{
	const auto difference = colliderCenter - ghostCenter;
	const auto pos = m_pOwner->GetComponent<Transform>()->GetWorldPosition();

	//if horizontal center y
	if (m_pOwner->GetComponent<DirectionComponent>()->GetDirection().y == 0)
	{
		m_pOwner->GetComponent<Transform>()->SetWorldPosition({ pos.x, pos.y + difference.y });
	}
	else
	{
		m_pOwner->GetComponent<Transform>()->SetWorldPosition({ pos.x + difference.x, pos.y });
	}
}

void GhostComponent::SetupTexture()
{
	switch (m_GhostNumber)
	{
	case 1:
		m_TexturePath = "GhostOrange.png";
		break;
	case 2:
		m_TexturePath = "GhostRed.png";
		break;
	case 3:
		m_TexturePath = "GhostBlue.png";
		break;

	case 4:
		m_TexturePath = "GhostPink.png";
		break;
	}

	m_pOwner->GetComponent<TextureRenderer>()->SetTexture(m_TexturePath);
}

State* GhostComponent::GetRandomPossibleState() const
{
	//It would be best using a registration mechanism where each state type registers itself with the factory
	//Todo: Implement a registration mechanism for the states When there is time left.

	switch (m_GhostNumber)
	{
	case 1:
	{
		//Clyde Clyde alternates between chasing and fleeing.
		const auto number = std::rand() % 2;
		if (number)
		{
			return new ChaseState(m_pOwner);
		}

		return new ScatterState(m_pOwner);
		break;
	}

	case 2: {
		//Blinky
		return new ChaseState(m_pOwner);
		break;
	}
		  //Pinky and Inky
	case 3:
	{
		return new CorneringState(m_pOwner);
		break;
	}
	case 4:
	{

		return new CorneringState(m_pOwner);
		break;
	}

	}

	return nullptr;

}

void GhostComponent::Render()
{
#ifdef _DEBUG
	ServiceLocator::GetInstance().Renderer.GetService().RenderRect(m_Target, { 255,200,100 }, { 5,5 });
#endif // _DEBUG
}

glm::vec2 GhostComponent::GetRandomPossibleDirection(const std::vector<glm::vec2>& possibleDirections) const
{
	if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
	{
		const glm::vec2 oldDirection{ directionComponent->GetDirection() };

		// Create a list of valid new directions that are not opposite to the old direction
		std::vector<glm::vec2> validNewDirections;
		for (const auto& newDirection : possibleDirections)
		{
			if (glm::abs(glm::dot(newDirection, oldDirection) + 1.f) >= FLT_EPSILON)
			{
				validNewDirections.push_back(newDirection);
			}
		}

		if (validNewDirections.empty())
		{
			// No valid directions found, do not change direction
			assert(false && "No valid directions found, do not change direction");
			return { 1,0 };
		}

		// Select a random valid new direction
		const int randomIndex = std::rand() % validNewDirections.size();
		return validNewDirections[randomIndex];
	}
	else
	{
		assert(false && "No DirectionComponent found");
	}

	return { 1,0 };
}

glm::vec2 GhostComponent::GetDirectionOfVector(const std::vector<glm::vec2>& possibleDirections, const glm::vec2& target) const
{
	const auto desiredDirection = CalculateDirection(target);
	const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>();

	//Go over every possible direction. 
	for (const auto& direction : possibleDirections)
	{
		// If the desired direction is available, set that direction
		if (direction == desiredDirection)
		{
			// Calculate the dot product between the desired direction and the current direction
			const float dotProduct = glm::dot(desiredDirection, directionComponent->GetDirection());

			// If the dot product is -1, it's a 180-degree turn, so skip it
			if (glm::abs(dotProduct + 1.0f) < std::numeric_limits<float>::epsilon())
			{
				continue;
			}


			return desiredDirection;
		}
	}

	// If the desired direction is not available, choose another direction
	const std::vector<glm::vec2> desiredDirections{ {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	for (const auto& desiredDir : desiredDirections)
	{
		// Calculate the dot product between the desired direction and the current direction
		const float dotProduct = glm::dot(desiredDir, directionComponent->GetDirection());

		// If the dot product is -1, it's a 180-degree turn, so skip it
		if (glm::abs(dotProduct + 1.0f) < std::numeric_limits<float>::epsilon())
		{
			continue;
		}

		// Check if the alternative direction is available
		for (const auto& direction : possibleDirections)
		{
			if (direction == desiredDir)
			{
				return desiredDir;
			}
		}
	}

	// If no valid direction is found
	std::cout << "glm::vec2 GhostComponent::GetDirectionOfVector(const std::vector<glm::vec2>& possibleDirections, const glm::vec2& target) const \n{\n\tNo Possible Direction Found;\n}";

	return  desiredDirection;
}

glm::vec2 GhostComponent::CalculateDirection(const glm::vec2& target) const
{
	const auto worldPos = m_pOwner->GetComponent<Transform>()->GetWorldPosition();
	const auto vector = target - worldPos;

	if (glm::abs(vector.x) > glm::abs(vector.y))
	{
		if (vector.x > 0)
		{
			return	{ 1,0 };
		}

		return	{ -1,0 };

	}

	if (vector.y > 0)
	{
		return{ 0,1 };
	}

	return { 0,-1 };
}

void GhostComponent::StorePacMan() const
{
	//--
	//Find pac Man
	//--

	const auto storage = m_pOwner->GetComponent<GameObjectStorage>();
	if (storage->GetStoredObject() == nullptr || storage->GetStoredObject()->GetComponent<PacManComponent>() == nullptr)
	{
		//Get All objects in the scene
		const auto objects = SceneManager::GetInstance().GetActiveScene()->GetObjects();

		//Find the object with the pacman component and store it in the ghost
		for (const auto& object : objects)
		{
			if (object->GetComponent<PacManComponent>())
			{
				storage->StoreGameObject(object);
			}
		}

		if (storage->GetStoredObject()->GetComponent<PacManComponent>() == nullptr)
		{
			assert(false && "Pacman not found");
		}
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
	if (spriteRenderer == nullptr) assert(false && "SpriteRenderer not found");

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

void GhostComponent::InitEyesSprites()
{
	const auto spriteRenderer = m_pOwner->GetComponent<SpriteRenderer>();
	spriteRenderer->ResetSpriteFrames();
	spriteRenderer->SetTexture("GhostEyes.png");


	const auto x = 16;
	for (size_t i{}; i < 3; ++i)
	{
		spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Down);
		spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Up);
		spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Left);
		spriteRenderer->AddSpriteFrame({ i * x, 0 }, MovementDirection::Right);
	}
}

void GhostComponent::SetupStates()
{
	m_pOwner->GetComponent<StateComponent>()->SetState(new IdleState{ m_pOwner });
}
