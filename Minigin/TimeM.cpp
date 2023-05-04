#include "TimeM.h"

float TimeM::GetElapsed() const
{
	return m_Elapsed;
}

float TimeM::GetDeltaTimeM() const
{
	return m_DeltaT;
}

void TimeM::Update(float deltaT)
{
	m_DeltaT = deltaT;
	m_Elapsed += deltaT;
}

