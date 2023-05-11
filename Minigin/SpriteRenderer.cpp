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

, m_ActionmapOffset{
{ Action::Move, {}},
{ Action::Attack, {}} }

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
				m_AnimationFrame = 1;
			}
			else if (m_AccumulatedFrameTime > m_FrameTime)
			{
				++m_AnimationFrame %= m_MovementDirectionMap.find(m_MovementDirection)->second.size();


				m_AccumulatedFrameTime = 0.f;
			}
		}

		//Non Moving Objects
		else
		{
			if (m_AccumulatedFrameTime > m_FrameTime)
			{
				++m_AnimationFrame %= m_MovementDirectionMap.find(m_MovementDirection)->second.size();
				m_AccumulatedFrameTime -= m_FrameTime;
			}
		}
	}

	SetSourceRect(m_MovementDirectionMap.find(m_MovementDirection)->second[m_AnimationFrame]);
}

void SpriteRenderer::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
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
	m_MovementDirection = value;
	m_AccumulatedMoveToStandstillTime = 0.f;
}

void SpriteRenderer::AddSpriteFrame(const glm::vec2& position, MovementDirection direction)
{
	m_MovementDirectionMap.find(direction)->second.push_back(position);
}

void SpriteRenderer::SetActionOffset(const glm::vec2& offset, Action action)
{
	m_ActionmapOffset.find(action)->second = offset;
}

void SpriteRenderer::SetSourceRect(const glm::vec2& position)
{
	auto pos = position;

	pos += m_ActionmapOffset.find(m_Action)->second;
	GetComponent<TextureRenderer>()->SetSourceRect(pos, m_SpriteSize);
}
