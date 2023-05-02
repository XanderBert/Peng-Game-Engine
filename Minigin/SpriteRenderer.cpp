#include "SpriteRenderer.h"
#include <stdexcept>
#include "InputManager.h"
#include "TextureRenderer.h"
#include "Time.h"

SpriteRenderer::SpriteRenderer(GameObject* owner)
	: Component(owner)

	, m_MovementDirectionMap{
		std::make_pair(MovementDirection::Up, glm::vec2{ 64,0 }),
		std::make_pair(MovementDirection::Down, glm::vec2{0,0}),
		std::make_pair(MovementDirection::Left, glm::vec2{32,0}),
		std::make_pair(MovementDirection::Right, glm::vec2{96,0}) }

		, m_TimeFromMovementToStandStill{ 0.3f }
{
	//SetSourceRect({ 0,0 }, { 16, 16 });

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
	const glm::vec2 basePosition = m_MovementDirectionMap.find(m_MovementDirection)->second;

	const auto elaspedTime{ Time::GetInstance().GetElapsed() };
	const auto elapsed = static_cast<int>(elaspedTime * 4) % 2;

	if (!elapsed)
	{
		SetSourceRect({ basePosition.x + 16, basePosition.y });
	}
	//Only play the full animation when you actually move
	else if (m_AccumulatedMoveToStandstillTime <= m_TimeFromMovementToStandStill)
	{
		SetSourceRect(basePosition);
	}

	m_AccumulatedMoveToStandstillTime += elaspedTime;
}

void SpriteRenderer::Render()
{
	GetComponent<TextureRenderer>()->Render();
}

void SpriteRenderer::SetTexture(const std::string& texturePath)
{
	GetComponent<TextureRenderer>()->SetTexture(texturePath);
}

void SpriteRenderer::SetSourceRect(const glm::vec2& position)
{
	GetComponent<TextureRenderer>()->SetSourceRect(position, m_SpriteSize);
}
