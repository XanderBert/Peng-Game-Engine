#pragma once
#include "Component.h"

class EndingScreenComponent final : public Component
{
public:
	EndingScreenComponent(GameObject* pParent);
	~EndingScreenComponent() override = default;

	EndingScreenComponent(const EndingScreenComponent& other) = delete;
	EndingScreenComponent(EndingScreenComponent&& other) noexcept = delete;
	EndingScreenComponent& operator=(const EndingScreenComponent& other) = delete;
	EndingScreenComponent& operator=(EndingScreenComponent&& other) noexcept = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStedp*/) override {}
	void LateUpdate() override {}
	void Render() override {}

};
