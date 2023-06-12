#pragma once
#include <SDL_keycode.h>
#include "Command.h"
#include "Component.h"
#include "InputManager.h"

class InputComponent final : public Component
{
public:
	InputComponent(GameObject* owner);
	virtual ~InputComponent()  override;

	InputComponent(const InputComponent& other) = delete;
	InputComponent(InputComponent&& other) = delete;
	InputComponent& operator=(const InputComponent& other) = delete;
	InputComponent& operator=(InputComponent&& other) = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float /*fixedTimeMStep*/) override {}

	//Called after the Update()c
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override {}

	//Called each frame
	virtual void Render() override {}

	void AddBinding(SDL_Keycode key, Command* command);
	std::unordered_map<SDL_Keycode, Command*>& GetKeyboardCommands() { return m_KeyboardCommands; }

	template<typename T>

	std::vector<SDL_Keycode> GetKeysOfCommand();

	void EnableInput();
	void DisableInput();
private:
	//I will use more memory by storing the commands twice.
	//But now i dont need to be searching trough all the commands to find wich one is from wich actor
	std::unordered_map<SDL_Keycode, Command*> m_KeyboardCommands{};
	null_InputManager* m_pInputManager;
	bool m_IsEnabled{ true };
};

template<typename T>
inline std::vector<SDL_Keycode> InputComponent::GetKeysOfCommand()
{
	std::vector<SDL_Keycode> keys;

	for (const auto& keyMap : m_KeyboardCommands)
	{
		if (dynamic_cast<T>(keyMap.second))
		{
			keys.emplace_back(keyMap.first);
		}
	}

	return keys;
}
