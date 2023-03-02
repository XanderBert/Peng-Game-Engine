#include "Color.h"

Color::Color() : Component() {};
Color::~Color() = default;

void Color::Update([[maybe_unused]] float deltaT)
{
}

void Color::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void Color::LateUpdate([[maybe_unused]] float deltaT)
{
}

void Color::Render() const
{
}

SDL_Color Color::GetColor() const
{
	return m_color;
}

void Color::SetColor(const SDL_Color& color)
{
	m_color = color;
}
