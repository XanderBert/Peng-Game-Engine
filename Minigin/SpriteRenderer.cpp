#include "SpriteRenderer.h"
#include <stdexcept>
#include "InputManager.h"
#include "TextureRenderer.h"
#include "TimeM.h"

//SpriteSize Needs to be set
//Sprite Frames Need to be added
SpriteRenderer::SpriteRenderer(GameObject* owner) : Component(owner)
, m_MovementDirectionMap{
{MovementDirection::Up, {}},
{MovementDirection::Down, {}},
{MovementDirection::Left, {}},
{MovementDirection::Right, {}},
{MovementDirection::None, {}} }

, m_FrameTime{ 0.3f }
, m_TimeFromMovementToStandStill{ 0.3f }
{
	if (GetComponent<TextureRenderer>() == nullptr)
	{
		throw std::runtime_error(std::string("Your GameObject needs an TextureRenderer Component for the SpriteRenderer To work"));
	}
}

SpriteRenderer::~SpriteRenderer() = default;

void SpriteRenderer::Update()
{
	if (m_IsPlaying)
	{
		const auto elapsedTime = TimeM::GetInstance().GetDeltaTimeM();

		m_AccumulatedFrameTime += elapsedTime;

		//Moving Objects
		if (m_MovementDirection != MovementDirection::None)
		{
			m_AccumulatedMoveToStandstillTime += elapsedTime;
			if (m_AccumulatedMoveToStandstillTime > m_TimeFromMovementToStandStill)
			{
				m_AnimationFrame = 0;
			}

			else
			{
				UpdateAnimationFrame();
			}
		}

		//Non Moving Objects
		else
		{
			UpdateAnimationFrame();
		}
	}

	SetSourceRect(m_MovementDirectionMap.find(m_MovementDirection)->second[m_AnimationFrame]);


}

void SpriteRenderer::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void SpriteRenderer::LateUpdate()
{
}

void SpriteRenderer::Render()
{
	GetComponent<TextureRenderer>()->Render();
}

void SpriteRenderer::SetTexture(const std::string& texturePath)
{
	GetComponent<TextureRenderer>()->SetTexture(texturePath);
}

void SpriteRenderer::SetMovementDirection(MovementDirection value)
{
	const auto size = m_MovementDirectionMap.find(m_MovementDirection)->second.size();
	if (static_cast<int>(size) < m_AnimationFrame) m_AnimationFrame = 0;

	m_MovementDirection = value;
	m_AccumulatedMoveToStandstillTime = 0.f;
}

void SpriteRenderer::SetMovementDirection(const glm::vec2& direction)
{
	if (direction.x > 0)
	{
		SetMovementDirection(MovementDirection::Right);
	}
	else if (direction.x < 0)
	{
		SetMovementDirection(MovementDirection::Left);
	}
	else if (direction.y > 0)
	{
		SetMovementDirection(MovementDirection::Down);
	}
	else
	{
		SetMovementDirection(MovementDirection::Up);
	}
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

void SpriteRenderer::SetSourceRect(const glm::vec2& position) const
{
	GetComponent<TextureRenderer>()->SetSourceRect(position + m_Offset, m_SpriteSize);
}

void SpriteRenderer::UpdateAnimationFrame()
{
	if (m_AccumulatedFrameTime > m_FrameTime)
	{
		const auto size = m_MovementDirectionMap.find(m_MovementDirection)->second.size();
		++m_AnimationFrame %= size;
		m_AccumulatedFrameTime = 0.f;
	}
}
