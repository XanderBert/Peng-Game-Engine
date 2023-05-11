#include "IceBlock.h"

#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"

IceBlock::IceBlock() : GameObject()
{
	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("Ice_Block.png");

	const auto sprite = AddComponent<SpriteRenderer>();
	sprite->SetSpriteSize(m_SpriteSize);

	for (size_t i{}; i < m_NrFrames; ++i)
	{
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::None);
	}

	sprite->SetMovementDirection(MovementDirection::None);
	sprite->Pause();
	sprite->SetFrameTime(0.05f);

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_SpriteSize);
}

IceBlock::~IceBlock()
{
}

void IceBlock::Update()
{
	GameObject::Update();

	UpdateMovement();
	UpdateSpriteLogic();
}

void IceBlock::OnCollision([[maybe_unused]] GameObject* other)
{
	if (m_Velocity != glm::vec2{ 0,0 })
	{
		GetComponent<SpriteRenderer>()->Play();
		m_Velocity = { 0,0 };
	}
}

void IceBlock::MoveIceBlock(const MovementDirection fireDirection)
{
	//Move this if it collides with wall/ice block. stop moving
	//when it cannot move in that direction it gets destroyed
	switch (fireDirection)
	{
	case MovementDirection::Up: m_Velocity = { 0, -100 }; break;
	case MovementDirection::Down: m_Velocity = { 0, 100 }; break;
	case MovementDirection::Left: m_Velocity = { -100, 0 }; break;
	case MovementDirection::Right: m_Velocity = { 100, 0 }; break;
	}
}

void IceBlock::UpdateMovement()
{
	//Get TransformComponent
	const auto transform = GetComponent<Transform>();
	//Get Local Psotion
	const auto pos = transform->GetLocalPosition();
	//Update Local Position with Velocity
	transform->SetLocalPosition(pos + (m_Velocity * TimeM::GetInstance().GetDeltaTimeM()));
}

void IceBlock::UpdateSpriteLogic()
{
	//Get SpriteComponent
	if (const auto spriteRenderer = GetComponent<SpriteRenderer>())
	{
		//Check if it is playing
		if (spriteRenderer->IsPlaying())
		{
			//Check if it is at the last frame
			if (spriteRenderer->GetCurrentSpriteIndexForCurrentDirection() == spriteRenderer->GetLastSpriteIndexForCurrentDirection())
			{
				//Stop playing and mark for deletion
				spriteRenderer->Pause();
				MarkForDeletion();
			}
		}
	}
}
