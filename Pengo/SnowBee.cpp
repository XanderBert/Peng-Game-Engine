#include "SnowBee.h"

#include "IceBlock.h"
#include "Pengo.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "TimeM.h"
#include "Transform.h"

SnowBee::SnowBee()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	textureRenderer->SetTexture("SnowBee.png");

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

	spriteRenderer->SetActionOffset({ 0,16 }, Action::Move);
	spriteRenderer->SetActionOffset({ 0,32 }, Action::Attack);
	spriteRenderer->SetAction(Action::Move);
	spriteRenderer->SetMovementDirection(m_Direction);
	spriteRenderer->Play();


	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize({ 16,16 });

	GetComponent<Transform>()->SetWorldPosition({ 250,250 });
}

void SnowBee::Update()
{
	GameObject::Update();
	Move();
}

void SnowBee::LateUpdate()
{
	GameObject::LateUpdate();
}

void SnowBee::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);

	if (const auto* pengo = dynamic_cast<Pengo*>(other))
	{
		//Kill the focking pengo
		//pengo->Kill();

	}

	if (dynamic_cast<IceBlock*>(other))
	{
		//Go goblin mode
		if (const auto spriteRenderer = GetComponent<SpriteRenderer>())
		{
			spriteRenderer->SetAction(Action::Attack);
		}
	}

	StopMovement();
	ChangeMovement();
}

void SnowBee::ChangeMovement()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator

	// Generate a random integer between 0 and 3
	const int numQuarterTurns = std::rand() % 4;

	// Perform the quarter turns
	for (int i = 0; i < numQuarterTurns; ++i)
	{
		const float temp = m_Direction.x;
		m_Direction.x = -m_Direction.y;
		m_Direction.y = temp;
	}
}

void SnowBee::Move() const
{
	if (const auto transform = GetComponent<Transform>())
	{
		const auto pos = transform->GetWorldPosition();
		const glm::vec2 newPos = pos + m_Direction * m_velocity * TimeM::GetInstance().GetDeltaTimeM();
		transform->SetWorldPosition(newPos);
	}

	//Will need to be triggered each frame to handle spriteSheet animation
	GetComponent<SpriteRenderer>()->SetMovementDirection(m_Direction);
}

void SnowBee::StopMovement() const
{
	if (const auto transform = GetComponent<Transform>())
	{
		transform->SetWorldPosition(transform->GetLastWorldPosition());
	}
}
