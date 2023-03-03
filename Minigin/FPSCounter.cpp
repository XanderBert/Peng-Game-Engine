#include "FPSCounter.h"
#include <iostream>
#include "Time.h"
#include "FontRenderer.h"


//needs: translate, font, font renderer
FPSCounter::FPSCounter() : Component() {};

FPSCounter::~FPSCounter() = default;

void FPSCounter::Update()
{
	CalculateFPS();

	if(const auto fontRenderer = GetComponent<FontRenderer>())
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

void FPSCounter::Render() const
{
}

std::string FPSCounter::GetFPSAsString() const
{
	return std::to_string(m_currentFPS);
}

std::string FPSCounter::GetFPSAsIntString() const
{
	return std::to_string(static_cast<int>(m_currentFPS));

}

void FPSCounter::CalculateFPS()
{
	//Increase precision by increasing the number
	constexpr int precision{ 100 };
	if (static_cast<int>(Time::GetInstance().GetElapsed() * precision) % precision == 0)
	{
		m_currentFPS = 1.f / Time::GetInstance().GetDeltaTime();
	}
}