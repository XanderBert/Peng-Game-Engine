#include "SpriteRenderer.h"
#include <stdexcept>
#include "InputManager.h"
#include "TextureRenderer.h"
#include "Time.h"

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
	//Todo Why does this function not get called????
	std::cout << " This Comp Updates???";
}

void SpriteRenderer::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void SpriteRenderer::LateUpdate()
{
	const auto elapsedTime = Time::GetInstance().GetDeltaTime();

	m_AccumulatedFrameTime += elapsedTime;
	m_AccumulatedMoveToStandstillTime += elapsedTime;

	if (m_AccumulatedMoveToStandstillTime > m_TimeFromMovementToStandStill)
	{
		m_AnimationFrame = 1;
	}
	else if (m_AccumulatedFrameTime > m_FrameTime)
	{
		++m_AnimationFrame %= m_MovementDirectionMap.find(m_MovementDirection)->second.size();
		m_AccumulatedFrameTime -= m_FrameTime;
	}


	SetSourceRect(m_MovementDirectionMap.find(m_MovementDirection)->second[m_AnimationFrame]);
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
