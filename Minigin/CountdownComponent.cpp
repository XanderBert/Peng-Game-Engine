#include "CountdownComponent.h"
#include "TimeM.h"

CountdownComponent::CountdownComponent(GameObject* owner)
	: Component(owner)
{}

CountdownComponent::~CountdownComponent() = default;

void CountdownComponent::Update()
{
	if (m_Play)
		m_Time -= TimeM::GetInstance().GetDeltaTimeM();
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
