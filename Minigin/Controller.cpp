#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "Controller.h"
#include <glm/vec2.hpp>
#include "SceneManager.h"

class Controller::ControllerImpl
{
public:
	ControllerImpl(int controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		m_ControllerIndex = controllerIndex;
	}

	void UpdateState()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		//There are 4 virtual ports numbered from 0-4 on witch a controller can be connected
		XInputGetState(m_ControllerIndex, &m_CurrentState);
	}

	void Update()
	{
		UpdateState();
		const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

	unsigned char GetbLeftTriggerValue() const { return m_CurrentState.Gamepad.bLeftTrigger; }
	unsigned char GetbRightTriggerValue() const { return m_CurrentState.Gamepad.bRightTrigger; }

	auto GetLeftThumbValue()const
	{
		float thumbLX{ static_cast<float>(m_CurrentState.Gamepad.sThumbLX) };
		float thumbLY{ static_cast<float>(m_CurrentState.Gamepad.sThumbLY) };

		//Normalize the value's
		const float normLX = thumbLX / SHRT_MAX;
		const float normLY = thumbLY / SHRT_MAX;

		//Adjust value's for the dead zone and remap the actual used value's from [0-1]
		//For example: there is a dead zone up to 0.2 -> then the controller will only give input from 0.2 up to 1.
		thumbLX = abs(normLX) < m_ThumbStickDeadZones.x ? 0 : (abs(normLX) - m_ThumbStickDeadZones.x) * (normLX / abs(normLX));
		thumbLY = abs(normLY) < m_ThumbStickDeadZones.y ? 0 : (abs(normLY) - m_ThumbStickDeadZones.y) * (normLY / (abs(normLY)));
		thumbLX /= 1.f - m_ThumbStickDeadZones.x;
		thumbLY /= 1.f - m_ThumbStickDeadZones.y;

		return  glm::vec2{ thumbLX, thumbLY };
	}

	auto GetRightThumbValue()
	{
		float thumbRX{ static_cast<float>(m_CurrentState.Gamepad.sThumbRX) };
		float thumbRY{ static_cast<float>(m_CurrentState.Gamepad.sThumbRY) };

		const float normRX = thumbRX / SHRT_MAX;
		const float normRY = thumbRY / SHRT_MAX;

		thumbRX = abs(normRX) < m_ThumbStickDeadZones.x ? 0 : (abs(normRX) - m_ThumbStickDeadZones.x) * (normRX / (abs(normRX)));
		thumbRY = abs(normRY) < m_ThumbStickDeadZones.y ? 0 : (abs(normRY) - m_ThumbStickDeadZones.y) * (normRY / (abs(normRY)));

		thumbRX /= 1.f - m_ThumbStickDeadZones.x;
		thumbRY /= 1.f - m_ThumbStickDeadZones.y;

		return  glm::vec2{ thumbRX, thumbRY };
	}

	int GetControllerID() const { return  m_ControllerIndex; }

	WORD GetButtonsPressedThisFrame() const { return m_ButtonsPressedThisFrame; }
	WORD GetButtonsPressed() const { return m_CurrentState.Gamepad.wButtons; }

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex{};

	const glm::vec2 m_ThumbStickDeadZones{ 0.05f, 0.02f };
};


Controller::Controller(int controllerIndex)
{
	pImpl = std::make_unique<ControllerImpl>(controllerIndex);
}

Controller::~Controller() = default;


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

BYTE Controller::GetbLeftTriggerValue() const
{
	return pImpl->GetbLeftTriggerValue();
}

unsigned char Controller::GetbRightTriggerValue() const
{
	return pImpl->GetbRightTriggerValue();
}

glm::vec<2, float, glm::defaultp> Controller::GetLeftThumbValue() const
{
	return pImpl->GetLeftThumbValue();
}

glm::vec<2, float, glm::defaultp> Controller::GetRightThumbValue() const
{
	return  pImpl->GetRightThumbValue();
}

int Controller::GetControllerID() const
{
	return pImpl->GetControllerID();
}

WORD Controller::GetPressedButtons() const
{
	return pImpl->GetButtonsPressed();
}


