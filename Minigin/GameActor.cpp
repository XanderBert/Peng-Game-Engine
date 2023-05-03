#include "GameActor.h"
#include <iostream>
#include "FontRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "Time.h"
#include "Transform.h"

GameActor::GameActor()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	//TODO: Set with function or in constructor?
	textureRenderer->SetTexture("Pengo.png");

	const auto spriteRenderer{ AddComponent<SpriteRenderer>() };
	spriteRenderer->SetSpriteSize({ 16,16 });

	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Right);

	InputManager::GetInstance().AddActor(this);
}

GameActor::~GameActor()
{

}

void GameActor::Update()
{
	//if (const auto fontRenderer = GetComponent<FontRenderer>())
	//{
	//	fontRenderer->SetText(std::to_string(m_Health));
	//}

}

void GameActor::Jump()
{
	//std::cout << "The actor Jumps!\n";
	//glm::vec2 pos = direction * speed * dt;
	//m_pActor->GetComponent<Transform>().get()->SetLocalPosition();
}

void GameActor::Move(const glm::vec2& direction)
{
	const auto transform = GetComponent<Transform>();
	const auto movement{ direction * m_Speed * Time::GetInstance().GetDeltaTime() };

	transform->SetLocalPosition(transform->GetLocalPosition() + movement);

	SetTextureDirection(direction);
}

void GameActor::Die()
{
	NotifyObserver(GameEvent::ActorDied);
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

	if (m_Points >= 100) NotifyObserver(GameEvent::Actor100Points);
}

void GameActor::SetControllerIndex(int index)
{
	m_UsesController = true;
	m_ControllerID = index;
	const auto& controllers = InputManager::GetInstance().GetControllers();

	for (const auto& controller : controllers)
	{
		if (controller->GetControllerID() == index)
		{
			controller->SetActor(this);
		}
	}

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
