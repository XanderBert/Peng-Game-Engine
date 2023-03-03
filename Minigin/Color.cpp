#include "Color.h"

Color::Color() : Component() {};
Color::~Color() = default;

void Color::Update()
{
}

void Color::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void Color::LateUpdate()
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
