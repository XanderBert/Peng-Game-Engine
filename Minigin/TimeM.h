#pragma once
#include "Singleton.h"
class TimeM final : public Singleton<TimeM>
{
public:
	float GetElapsed() const;
	float GetDeltaTimeM() const;

	void Update(float deltaT);

private:
	friend class Singleton<TimeM>;
	TimeM() = default;
	
	float m_DeltaT{};
	float m_Elapsed{};
};