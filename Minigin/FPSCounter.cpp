#include "FPSCounter.h"
#include "TimeM.h"
#include "FontRenderer.h"

//needs: translate, font, font renderer
FPSCounter::FPSCounter(GameObject* owner) : Component(owner)
{
}

FPSCounter::~FPSCounter() = default;

void FPSCounter::Update()
{

	const auto currentFps = m_currentFPS;
	CalculateFPS();

	//If the fps stayed the same do not update the text
	if (abs(m_currentFPS - currentFps) > 1.f)
	{
		if (const auto fontRenderer = m_pOwner->GetComponent<FontRenderer>())
		{
			fontRenderer->SetText(GetFPSAsIntString());
		}
	}
}

void FPSCounter::FixedUpdate(float /*fixedTimeMStep*/)
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

std::string FPSCounter::GetFPSAsIntString()
{
	return m_currentFPSString = std::to_string(static_cast<int>(m_currentFPS));
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