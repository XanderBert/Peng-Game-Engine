#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"

class Controller::ControllerImpl
{
public:
	ControllerImpl(int controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		m_ControllerIndex = controllerIndex;
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex{};
};


Controller::Controller(int controllerIndex)
{
	pImpl = std::make_unique<ControllerImpl>(controllerIndex);
}

Controller::~Controller()
{

}

void Controller::Update()
{
	pImpl->Update();
}

bool Controller::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool Controller::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}
