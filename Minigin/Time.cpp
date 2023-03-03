#include "Time.h"

float Time::GetElapsed() const
{
	return m_Elapsed;
}

float Time::GetDeltaTime() const
{
	return m_DeltaT;
}

void Time::Update(float deltaT)
{
	m_DeltaT = deltaT;
	m_Elapsed += deltaT;
}

