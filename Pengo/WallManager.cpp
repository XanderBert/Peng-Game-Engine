l#include "WallManager.h"
#include "BoxCollider.h"
#include "DirectionComponent.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "CountdownComponent.h"
#include "TriggerComponent.h"

WallManager::WallManager() : GameObject()
{
	SetTag("WallManager");

	for (size_t i = 0; i < 2; ++i)
	{
		const auto horizontalWall = new GameObject{};
		horizontalWall->SetTag("Wall");

		horizontalWall->AddComponent<TextureRenderer>()->SetTexture("Wall_Horizontal.png");

		const auto spriteRenderer = horizontalWall->AddComponent<SpriteRenderer>();
		spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::None);
		spriteRenderer->AddSpriteFrame({ 0,8 }, MovementDirection::None);
		spriteRenderer->AddSpriteFrame({ 0,16 }, MovementDirection::None);
		spriteRenderer->SetSpriteSize(m_HorizontalWallSize);
		spriteRenderer->SetFrameTime(0.1f);
		spriteRenderer->Pause();

		const auto boxCollider = horizontalWall->AddComponent<BoxCollider>();
		boxCollider->SetColliderSize(m_HorizontalWallSize);

		const auto directionComponent = horizontalWall->AddComponent<DirectionComponent>();
		directionComponent->SetDirection({ 0,0 });

		horizontalWall->GetComponent<Transform>()->SetWorldPosition({ m_WallOffset,m_WallOffset + m_VerticalWallSize.y * i });

		horizontalWall->AddComponent<CountdownComponent>()->SetTime(m_TimeUntilMovingStateIsOver);

		const auto trigger = horizontalWall->AddComponent<TriggerComponent>();
		trigger->SetColliderSize({ m_HorizontalWallSize.x + 8, m_HorizontalWallSize.y + 8 });
		trigger->SetColliderOffset({ -4,-4 });
		trigger->SetTag("WallTrigger");



		m_pWalls.emplace_back(horizontalWall);
	}

	for (size_t i = 0; i < 2; ++i)
	{
		const auto verticalWall = new GameObject{};
		verticalWall->SetTag("Wall");

		verticalWall->AddComponent<TextureRenderer>()->SetTexture("Wall_Vertical.png");

		const auto spriteRenderer = verticalWall->AddComponent<SpriteRenderer>();
		spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::None);
		spriteRenderer->AddSpriteFrame({ 8,0 }, MovementDirection::None);
		spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::None);
		spriteRenderer->SetSpriteSize(m_VerticalWallSize);
		spriteRenderer->SetFrameTime(0.1f);
		spriteRenderer->Pause();

		const auto boxCollider = verticalWall->AddComponent<BoxCollider>();
		boxCollider->SetColliderSize(m_VerticalWallSize);

		const auto directionComponent = verticalWall->AddComponent<DirectionComponent>();
		directionComponent->SetDirection({ 0,0 });

		verticalWall->GetComponent<Transform>()->SetWorldPosition({ m_WallOffset + ((m_HorizontalWallSize.x - m_HorizontalWallSize.y) * i),m_WallOffset });
		verticalWall->AddComponent<CountdownComponent>()->SetTime(m_TimeUntilMovingStateIsOver);


		const auto trigger = verticalWall->AddComponent<TriggerComponent>();
		trigger->SetColliderSize({ m_VerticalWallSize.x + 8, m_VerticalWallSize.y + 8 });
		trigger->SetColliderOffset({ -4,-4 });
		trigger->SetTag("WallTrigger");

		m_pWalls.emplace_back(verticalWall);
	}

}

void WallManager::Update()
{
	GameObject::Update();

	for (const auto wall : m_pWalls)
	{
		if (const auto countDown = wall->GetComponent<CountdownComponent>())
		{
			if (const auto spriteRenderer = wall->GetComponent<SpriteRenderer>())
			{
				if (countDown->IsTimeUp())
				{
					spriteRenderer->SetAnimationFrame(0);
					spriteRenderer->Pause();
					countDown->Pause();
					countDown->ResetTime();

				}
			}
		}
	}
}

void WallManager::FixedUpdate(float fixedTimeMStep)
{
	GameObject::FixedUpdate(fixedTimeMStep);
}

void WallManager::LateUpdate()
{
	GameObject::LateUpdate();
}

void WallManager::Render() const
{
	GameObject::Render();
}
