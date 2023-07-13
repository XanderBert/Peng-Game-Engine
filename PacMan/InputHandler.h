#pragma once
#include "Component.h"
#include "ControllerComponent.h"
#include "InputComponent.h"

class InputHandler final : public Component 
{
public:
	InputHandler(GameObject* pParent);
	~InputHandler() override = default;

	InputHandler(const InputHandler& other) = delete;
	InputHandler(InputHandler&& other) = delete;
	InputHandler& operator=(const InputHandler& other) = delete;
	InputHandler& operator=(InputHandler&& other) = delete;

	void Update() override;
	void FixedUpdate(float fixedTimeMStep) override;
	void LateUpdate() override;
	void Render() override;


private:
	ControllerComponent* m_pController;
	InputComponent* m_pKeyboard;
};

