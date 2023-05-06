#include "SpriteRenderer.h"
#include <stdexcept>
#include "InputManager.h"
#include "TextureRenderer.h"
#include "TimeM.h"

//SpriteSize Needs to be set
//Sprite Frames Need to be added
SpriteRenderer::SpriteRenderer(GameObject* owner)
	: Component(owner)
	, m_MovementDirectionMap{
		{MovementDirection::Up, {}},
		{MovementDirection::Down, {}},
		{MovementDirection::Left, {}},
		{MovementDirection::Right, {}},
		{MovementDirection::None, {}} }

		, m_FrameTimeM{ 0.3f }
	, m_TimeMFromMovementToStandStill{ 0.3f }
{
	if (GetComponent<TextureRenderer>() == nullptr)
	{
		throw std::runtime_error(std::string("Your GameObject needs an TextureRenderer Component for the SpriteRenderer To work"));
	}
}

SpriteRenderer::~SpriteRenderer() = default;

void SpriteRenderer::Update()
{
	const auto elapsedTimeM = TimeM::GetInstance().GetDeltaTimeM();

	m_AccumulatedFrameTimeM += elapsedTimeM;
	m_AccumulatedMoveToStandstillTimeM += elapsedTimeM;

	if (m_AccumulatedMoveToStandstillTimeM > m_TimeMFromMovementToStandStill)
	{
		m_AnimationFrame = 1;
	}
	else if (m_AccumulatedFrameTimeM > m_FrameTimeM)
	{
		++m_AnimationFrame %= m_MovementDirectionMap.find(m_MovementDirection)->second.size();
		m_AccumulatedFrameTimeM -= m_FrameTimeM;
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

void SpriteRenderer::AddSpriteFrame(const glm::vec2& position, MovementDirection direction)
{
	m_MovementDirectionMap.find(direction)->second.push_back(position);
}
void SpriteRenderer::SetSourceRect(const glm::vec2& position)
{
	GetComponent<TextureRenderer>()->SetSourceRect(position, m_SpriteSize);
}
