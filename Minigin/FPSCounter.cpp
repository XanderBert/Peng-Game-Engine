#include "FPSCounter.h"
#include <iostream>
#include "Time.h"
#include "FontRenderer.h"


//needs: translate, font, font renderer
FPSCounter::FPSCounter(GameObject* owner) : Component(owner) {};

FPSCounter::~FPSCounter() = default;

void FPSCounter::Update()
{
	CalculateFPS();

	if (const auto fontRenderer = GetComponent<FontRenderer>())
	{
		fontRenderer->SetText(GetFPSAsIntString());
	}
}

void FPSCounter::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void FPSCounter::LateUpdate()
{
}

void FPSCounter::Render()
{
}

std::string FPSCounter::GetFPSAsString() const
{
	return std::to_string(m_currentFPS);
}

std::string* FPSCounter::GetFPSAsIntString()
{
	m_currentFPSString = std::to_string(static_cast<int>(m_currentFPS));
	return &m_currentFPSString;

}

void FPSCounter::CalculateFPS()
{
	//Increase precision by increasing the number
	constexpr int precision{ 100 };
	if (static_cast<int>(Time::GetInstance().GetElapsed() * precision) % precision <= FLT_EPSILON)
	{
		m_currentFPS = 1.f / Time::GetInstance().GetDeltaTime();
	}
}