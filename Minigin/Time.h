#pragma once
#include "Singleton.h"
class Time final : public Singleton<Time>
{
public:
	float GetElapsed() const;
	float GetDeltaTime() const;

	void Update(float deltaT);

private:
	friend class Singleton<Time>;
	Time() = default;
	
	float m_DeltaT{};
	float m_Elapsed{};
};

