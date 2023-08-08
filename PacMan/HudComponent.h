#pragma once
#include "Component.h"
#include "FontRenderer.h"

class HudComponent final : public Component
{
public:
	HudComponent(GameObject* pParent) : Component(pParent) {}
	~HudComponent() override = default;

	HudComponent(const HudComponent& other) = delete;
	HudComponent(HudComponent&& other) = delete;
	HudComponent& operator=(const HudComponent& other) = delete;
	HudComponent& operator=(HudComponent&& other) = delete;

	void Update() override;
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	void SetLives(const int lives) { m_Lives = lives; }

private:
	int m_Lives;
	int m_OldLives;
};

inline void HudComponent::Update()
{

	if(m_OldLives != m_Lives)
	{
		const auto font = m_pOwner->GetComponent<FontRenderer>();
		font->SetText("Lives: " + std::to_string(m_Lives));
		m_OldLives = m_Lives;
	}
}
