#include "CountdownComponent.h"

#include <iostream>

#include "TimeM.h"

CountdownComponent::CountdownComponent(GameObject* owner)
	: Component(owner)
{}

CountdownComponent::~CountdownComponent() = default;

void CountdownComponent::Update()
{
	if (m_Play)
		m_Time -= TimeM::GetInstance().GetDeltaTimeM();

	if (m_DebugMode)
		std::cout << "Time: " << m_Time << std::endl;
}

void CountdownComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void CountdownComponent::LateUpdate()
{
}

void CountdownComponent::Render()
{
}
