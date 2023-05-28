#pragma once
#include <SDL_keycode.h>

#include "Command.h"
#include "Component.h"
#include "InputManager.h"

class InputComponent final : public Component
{
public:
	InputComponent(GameObject* owner);
	~InputComponent() = default;

	InputComponent(const InputComponent& other) = delete;
	InputComponent(InputComponent&& other) = delete;
	InputComponent& operator=(const InputComponent& other) = delete;
	InputComponent& operator=(InputComponent&& other) = delete;

	//Called each frame
	virtual void Update() override {}

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float /*fixedTimeMStep*/) override {}

	//Called after the Update()c
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override {}

	//Called each frame
	virtual void Render() override {}

	void AddBinding(SDL_Keycode key, Command* command);
private:
	null_InputManager* m_pInputManager;
};
