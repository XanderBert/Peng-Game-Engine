#include "GameActor.h"
#include <iostream>
#include "BoxCollider.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "TimeM.h"
#include "Transform.h"

GameActor::GameActor() : GameObject()
{
	ServiceLocator::GetInstance().InputManager.GetService().AddActor(this);
}

GameActor::~GameActor()
{
}

void GameActor::Update()
{
	GameObject::Update();
}

void GameActor::Jump()
{
}

void GameActor::Move(const glm::vec2& direction)
{
	const auto transform = GetComponent<Transform>();
	const auto movement{ direction * m_Speed * TimeM::GetInstance().GetDeltaTimeM() };

	transform->SetLocalPosition(transform->GetLocalPosition() + movement);

	SetTextureDirection(direction);
}

void GameActor::Die()
{
	MarkForDeletion();
}

void GameActor::TakeDammage(const int dammage)
{
	if (!m_Health) return;

	m_Health -= dammage;
	m_HealthString = std::to_string(m_Health);

	if (!m_Health) Die();
}

void GameActor::GainPoints(int ammountOfPoints)
{
	m_Points += ammountOfPoints;
	m_PointString = std::to_string(m_Points);
}

void GameActor::SetControllerIndex(int index)
{
	m_UsesController = true;
	m_ControllerID = index;
	const auto& controllers = ServiceLocator::GetInstance().InputManager.GetService().GetControllers();

	for (const auto& controller : controllers)
	{
		if (controller->GetControllerID() == index)
		{
			controller->SetActor(this);
		}
	}

}

void GameActor::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);
}

void GameActor::SetTextureDirection(const glm::vec2& direction)
{
	//When a sprite component is added it will update the direction
	if (const auto spriteComponent = GetComponent<SpriteRenderer>())
	{
		//Set Texture Direction
		float absX = std::abs(direction.x);
		float absY = std::abs(direction.y);

		// Compare magnitudes to determine dominant axis
		if (absX > absY)
		{
			// X-axis is dominant
			if (direction.x > 0)
			{
				spriteComponent->SetMovementDirection(MovementDirection::Right);
			}
			else
			{
				spriteComponent->SetMovementDirection(MovementDirection::Left);
			}
		}
		else
		{
			// Y-axis is dominant
			if (direction.y > 0)
			{
				spriteComponent->SetMovementDirection(MovementDirection::Down);
			}
			else
			{
				spriteComponent->SetMovementDirection(MovementDirection::Up);
			}
		}
	}
}