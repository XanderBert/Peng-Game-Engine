#pragma once
#include "Component.h"
#include "Transform.h"

class TeleportComponent final : public Component
{
public:
	TeleportComponent(GameObject* pParent) : Component(pParent) {}
	~TeleportComponent() override = default;

	TeleportComponent(const TeleportComponent& other) = delete;
	TeleportComponent(TeleportComponent&& other) = delete;
	TeleportComponent& operator=(const TeleportComponent& other) = delete;
	TeleportComponent& operator=(TeleportComponent&& other) = delete;

	void Update() override;
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}
};

inline void TeleportComponent::Update()
{
	const auto transform = m_pOwner->GetComponent<Transform>();
	const auto pos = transform->GetWorldPosition();
	if (pos.x < 0)
	{
		transform->SetWorldPosition({ 220, pos.y });
	}
	else if (pos.x > 220)
	{
		transform->SetWorldPosition({ 0, pos.y });
	}
}
