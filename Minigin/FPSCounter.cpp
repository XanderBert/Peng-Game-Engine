#include "FPSCounter.h"
#include <iostream>
#include "TimeM.h"
#include "FontRenderer.h"


//needs: translate, font, font renderer
FPSCounter::FPSCounter(GameObject* owner) : Component(owner) {}

FPSCounter::~FPSCounter() = default;

void FPSCounter::Update()
{
	CalculateFPS();

	//Todo Set the fetchcomponent as member.
	if (const auto fontRenderer = GetComponent<FontRenderer>())
	{
		fontRenderer->SetText(GetFPSAsIntString());
	}
}

void FPSCounter::FixedUpdate([[maybe_unused]] float fixedTimeMStep)
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
	if (static_cast<int>(TimeM::GetInstance().GetElapsed() * precision) % precision <= FLT_EPSILON)
	{
		m_currentFPS = 1.f / TimeM::GetInstance().GetDeltaTimeM();
	}
}