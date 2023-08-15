#pragma once
#include "CollisionManager.h"
#include "Component.h"
#include "InputManager.h"

class StartScreenComponent final : public Component
{
public:
	StartScreenComponent(GameObject* pParent);
	~StartScreenComponent() override = default;

	StartScreenComponent(const StartScreenComponent& other) = delete;
	StartScreenComponent(StartScreenComponent&& other) = delete;
	StartScreenComponent& operator=(const StartScreenComponent& other) = delete;
	StartScreenComponent& operator=(StartScreenComponent&& other) = delete;

	void Update() override;
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

private:
	null_InputManager& m_pInputManager;
	null_CollisionManager& m_pCollisionManager;
};
