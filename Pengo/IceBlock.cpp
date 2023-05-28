#include "IceBlock.h"

#include "BoxCollider.h"
#include "IceBlockTrigger.h"
#include "Pengo.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"

IceBlock::IceBlock()
	: GameObject()
	, m_pTrgger{ new IceBlockTrigger(this) }

{
	SetDirection({ 0, 0 });

	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("Ice_Block.png");

	const auto sprite = AddComponent<SpriteRenderer>();
	sprite->SetSpriteSize(m_SpriteSize);

	for (size_t i{}; i < m_NrFrames; ++i)
	{
		sprite->AddSpriteFrame({ 0 + i * 16,0 }, MovementDirection::None);
	}


	sprite->Pause();
	sprite->SetFrameTime(0.05f);

	const auto collision = AddComponent<BoxCollider>();
	collision->SetColliderSize(m_SpriteSize);
}

IceBlock::~IceBlock() = default;

void IceBlock::Update()
{
	GameObject::Update();

	UpdateMovement();
	UpdateSpriteLogic();
}

void IceBlock::OnCollision(GameObject* other)
{
	//Stop the block when it collides again an play the animation.
	if (other == m_pTrgger || dynamic_cast<Pengo*>(other) || dynamic_cast<PengoIceBlockTrigger*>(other))
	{
		return;
	}

	if (m_IsMoving)
	{
		GetComponent<SpriteRenderer>()->Play();
		m_FireDirection = { 0,0 };
	}
}

void IceBlock::MoveIceBlock(glm::vec2 direction)
{
	m_FireDirection = { direction.x * m_Velocity, direction.y * m_Velocity };
	m_IsMoving = true;
}

bool IceBlock::IsMoving() const
{
	return m_IsMoving;
}

void IceBlock::UpdateMovement()
{
	if (m_IsMoving)
	{
		//Get TransformComponent
		const auto transform = GetComponent<Transform>();
		//Get Local Position
		const auto pos = transform->GetLocalPosition();
		//Update Local Position with Velocity
		transform->SetLocalPosition(pos + (m_FireDirection * TimeM::GetInstance().GetDeltaTimeM()));
	}
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
			if (spriteRenderer->IsAnimationFinished())
			{
				//Stop playing and mark for deletion
				spriteRenderer->Pause();
				MarkForDeletion();
			}
		}
	}
}
