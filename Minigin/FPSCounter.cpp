#include "FPSCounter.h"

#include <iostream>

FPSCounter::FPSCounter() : Component() {};

FPSCounter::~FPSCounter() = default;

void FPSCounter::Update(float deltaT)
{
	CalculateFPS(deltaT);
}

void FPSCounter::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void FPSCounter::LateUpdate([[maybe_unused]] float deltaT)
{
}

void FPSCounter::Render() const
{
}

std::string FPSCounter::GetFPSAsString() const
{
	return std::to_string(m_currentFPS);
}

void FPSCounter::CalculateFPS(float deltaT)
{
	//auto measurement = 1.f / deltaT;
	//constexpr float smoothing = 0.9f; // larger=more smoothing

	//measurement = (measurement * smoothing) + (m_currentFPS * (1.0 - smoothing));

	m_currentFPS = 1.f / deltaT;
	std::cout << GetFPSAsString() << '\n';
}