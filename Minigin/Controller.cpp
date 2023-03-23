#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"

#include <glm/vec2.hpp>

#include "GameActor.h"
#include "Scene.h"
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

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		//wButtons
		const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		PressedStart();
	}

	bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

	unsigned char GetbLeftTriggerValue() const { return m_CurrentState.Gamepad.bLeftTrigger; }
	unsigned char GetbRightTriggerValue() const { return m_CurrentState.Gamepad.bRightTrigger; }

	auto GetLeftThumbValue()
	{
		float thumbLX{ static_cast<float>(m_CurrentState.Gamepad.sThumbLX) };
		float thumbLY{ static_cast<float>(m_CurrentState.Gamepad.sThumbLY) };

		const float normLX = thumbLX / SHRT_MAX;
		const float normLY = thumbLY / SHRT_MAX;

		thumbLX = abs(normLX) < m_ThumbStickDeadZones.x ? 0 : (abs(normLX) - m_ThumbStickDeadZones.x) * (normLX / (abs(normLX)));
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
	GameActor* GetGameActor() const { return m_pActor; }
	bool GetIsInUse() const { return m_IsInUse; }

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex{};

	const glm::vec2 m_ThumbStickDeadZones{ 0.05f, 0.02f };

	GameActor* m_pActor{ nullptr };

	bool m_IsInUse{ false };
	void PressedStart()
	{
		if (!m_IsInUse)
		{
			if (IsDownThisFrame(static_cast<unsigned int>(ControllerButton::Start)))
			{
				//What if i make an actor 

				//Makes a actor, adds it to the scene
				m_IsInUse = true;
				auto ga = new GameActor();
				ga->SetUsesController(true);
				m_pActor = ga;

				//Get Active Scene?
				auto* scene = SceneManager::GetInstance().GetSceneByName("Demo");
				if (scene != nullptr) { scene->Add(ga); }
			}
		}
	}
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

GameActor* Controller::GetGameActor() const
{
	return pImpl->GetGameActor();
}

bool Controller::GetIsInUse() const
{
	return pImpl->GetIsInUse();
}