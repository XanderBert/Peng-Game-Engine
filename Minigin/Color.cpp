#include "Color.h"

Color::Color(GameObject* owner) : Component(owner) {};
Color::~Color() = default;

void Color::Update()
{
}

void Color::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
{
}

void Color::LateUpdate()
{
}

void Color::Render()
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
