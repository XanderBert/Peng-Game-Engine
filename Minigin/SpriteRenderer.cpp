#include "SpriteRenderer.h"
#include <stdexcept>
#include "DirectionComponent.h"
#include "InputManager.h"
#include "TextureRenderer.h"
#include "TimeM.h"

//SpriteSize Needs to be set
//Sprite Frames Need to be added
SpriteRenderer::SpriteRenderer(GameObject* owner) : Component(owner)
, m_MovementDirectionMap
{
{MovementDirection::Up, {}},
{MovementDirection::Down, {}},
{MovementDirection::Left, {}},
{MovementDirection::Right, {}},
{MovementDirection::None, {}}
}

, m_AnimationFrame{ 0 }
, m_AccumulatedFrameTime{ 0.f }
, m_FrameTime{ 0.5f }
{
	if (m_pOwner->GetComponent<TextureRenderer>() == nullptr)
	{
		throw std::runtime_error(std::string("Your GameObject needs an TextureRenderer Component for the SpriteRenderer To work"));
	}
}

SpriteRenderer::~SpriteRenderer() = default;

void SpriteRenderer::Update()
{
	if (m_IsNotInit)
	{
		m_IsNotInit = false;
		m_AnimationFrame = 0;

		if (const auto direction = m_pOwner->GetComponent<DirectionComponent>())
		{
			SetMovementDirection(direction->GetDirection());
		}
		else
		{
			SetMovementDirection(MovementDirection::None);
		}

		SetSourceRect(m_MovementDirectionMap.find(m_MovementDirection)->second[0]);
	}

	if (m_IsPlaying)
	{
		//Set Texture Direction
		if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
		{
			//if (directionComponent->GetDirection() == m_MovementDirection)

			SetMovementDirection(directionComponent->GetDirection());
		}
		else
		{
			SetMovementDirection(MovementDirection::None);
		}


		const auto elapsedTime = TimeM::GetInstance().GetDeltaTimeM();
		m_AccumulatedFrameTime += elapsedTime;


		UpdateAnimationFrame();
		SetSourceRect(m_MovementDirectionMap.find(m_MovementDirection)->second[m_AnimationFrame]);
	}
}

void SpriteRenderer::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void SpriteRenderer::LateUpdate()
{
}

void SpriteRenderer::Render()
{
	m_pOwner->GetComponent<TextureRenderer>()->Render();
}

void SpriteRenderer::SetTexture(const std::string& texturePath)
{
	m_pOwner->GetComponent<TextureRenderer>()->SetTexture(texturePath);
}

void SpriteRenderer::SetMovementDirection(MovementDirection value)
{
	m_MovementDirection = value;
	const auto size = m_MovementDirectionMap.find(m_MovementDirection)->second.size();
	m_AnimationFrame %= size;
}

MovementDirection SpriteRenderer::ConvertMovementDirection(const glm::vec2& direction)
{
	if (direction.x > 0)
	{
		return MovementDirection::Right;

	}
	else if (direction.x < 0)
	{
		return MovementDirection::Left;
	}
	else if (direction.y > 0)
	{
		return MovementDirection::Down;
	}
	else if (direction.y < 0)
	{
		return MovementDirection::Up;
	}
	else
	{
		return MovementDirection::None;
	}
}

void SpriteRenderer::SetAnimationFrame(int animationFrame)
{
	if (m_MovementDirectionMap.find(m_MovementDirection)->second.size() < static_cast<unsigned int>(animationFrame))
	{
		throw std::exception("Animation frame out of range");
	}
	m_AnimationFrame = animationFrame;
	SetSourceRect(m_MovementDirectionMap.find(m_MovementDirection)->second[m_AnimationFrame]);

}

void SpriteRenderer::SetMovementDirection(const glm::vec2& direction)
{
	//const auto oldDirection = m_pOwner->GetComponent<DirectionComponent>()->GetPreviousDirection();

	//if (direction == oldDirection)
	//{
	//	return;
	//}

	SetMovementDirection(ConvertMovementDirection(direction));
}

glm::vec2 SpriteRenderer::GetMovementDirectionVector() const
{
	if (m_MovementDirection == MovementDirection::Down)
	{
		return { 0,1 };
	}
	else if (m_MovementDirection == MovementDirection::Left)
	{
		return { -1,0 };
	}
	else if (m_MovementDirection == MovementDirection::Right)
	{
		return { 1,0 };
	}
	else if (m_MovementDirection == MovementDirection::Up)
	{
		return { 0,-1 };
	}
	else
	{
		return { 0,0 };
	}
}

void SpriteRenderer::AddSpriteFrame(const glm::vec2& position, MovementDirection direction)
{
	m_MovementDirectionMap.find(direction)->second.push_back(position);
}

void SpriteRenderer::SetOffset(const glm::vec2& offset)
{
	m_Offset = offset;
}

void SpriteRenderer::Play()
{
	m_IsPlaying = true;
}

void SpriteRenderer::Pause()
{
	m_IsPlaying = false;
}

bool SpriteRenderer::IsPlaying() const
{
	return  m_IsPlaying;
}

void SpriteRenderer::SetSourceRect(const glm::vec2& position) const
{
	m_pOwner->GetComponent<TextureRenderer>()->SetSourceRect(position + m_Offset, m_SpriteSize);
}

void SpriteRenderer::UpdateAnimationFrame()
{
	if (m_AccumulatedFrameTime > m_FrameTime)
	{
		++m_AnimationFrame;
		m_AccumulatedFrameTime = 0.f;
	}
	const auto size = m_MovementDirectionMap.find(m_MovementDirection)->second.size();
	m_AnimationFrame %= size;
}
