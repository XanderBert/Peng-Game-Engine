#pragma once
#include <Component.h>
#include "PacManState.h"

class StateComponent final :public Component
{
public:
	StateComponent(GameObject* pOwner);
	~StateComponent() override = default;

	StateComponent(const StateComponent& other) = delete;
	StateComponent(StateComponent&& other) = delete;
	StateComponent& operator=(const StateComponent& other) = delete;
	StateComponent& operator=(StateComponent&& other) = delete;

	void Update() override;
	void FixedUpdate(float fixedTimeMStep) override;
	void LateUpdate() override;
	void Render() override;
	void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

	void SetState(State* pState);
private:
	std::unique_ptr<State> m_pState;
};