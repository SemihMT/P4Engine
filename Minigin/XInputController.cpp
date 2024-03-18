#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")
#include "XInputController.h"

using namespace dae;

class XInputController::XInputControllerImpl
{

public:
	explicit XInputControllerImpl(int controllerIdx) : m_ControllerIdx(controllerIdx)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}



	void Update()
	{
		//copy current state to previous state
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		//reset current state
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		//Get the current input state of this controller:
		const DWORD dwResult = XInputGetState(m_ControllerIdx, &m_CurrentState);
		if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
		{
			printf_s("Controller not connected\n");
		}
		if (dwResult == ERROR_SUCCESS)
		{
			//bitwise XOR (^)
			// p  q    p+q
			//
			// 0  0	 	0
			// 0  1	 	1
			// 1  0		1
			// 1  1	 	0

			//buttonChanges = whatever new input we're reading this frame
			const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;

			m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

			
			CalculateThumbSticks();
		}

	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}
	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}
	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}
	const glm::vec2& GetLeftThumbDir() const
	{
		return m_LeftThumbStickDir;
	}
	const glm::vec2& GetRightThumbDir() const
	{
		return m_RightThumbStickDir;
	}
	int GetControllerIndex() const
	{
		return m_ControllerIdx;
	}
private:


	void CalculateThumbSticks()
	{
		//From: https://learn.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
			//Left Thumbstick
		{
			const float LX = m_CurrentState.Gamepad.sThumbLX;
			const float LY = m_CurrentState.Gamepad.sThumbLY;

			float magnitudeL = sqrtf(LX * LX + LY * LY);

			const float normalizedLX = LX / magnitudeL;
			const float normalizedLY = LY / magnitudeL;


			float normalizedMagnitudeL = 0;
			if (magnitudeL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				//clipping magnitude at max possible value
				if (magnitudeL > 32767)
				{
					magnitudeL = 32767;
				}

				magnitudeL -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
				//0.0 to 1.0 range
				normalizedMagnitudeL = magnitudeL / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);


			}
			else
			{
				magnitudeL = 0.f;
				normalizedMagnitudeL = 0.f;
			}
			//{LX,LY} = direction vector, normalizedMagnitudeL = magnitude.
			m_LeftThumbStickDir.x = normalizedLX * normalizedMagnitudeL;
			m_LeftThumbStickDir.y = normalizedLY * normalizedMagnitudeL;
		}
		//Right Thumbstick
		{
			const float RX = m_CurrentState.Gamepad.sThumbRX;
			const float RY = m_CurrentState.Gamepad.sThumbRY;

			float magnitudeR = sqrtf(RX * RX + RY * RY);

			const float normalizedRX = RX / magnitudeR;
			const float normalizedRY = RY / magnitudeR;

			float normalizedMagnitudeR = 0;
			if (magnitudeR > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				//clipping magnitude at max possible value
				if (magnitudeR > 32767)
				{
					magnitudeR = 32767;
				}

				magnitudeR -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

				normalizedMagnitudeR = magnitudeR / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
			}
			else
			{
				magnitudeR = 0.f;
				normalizedMagnitudeR = 0.f;
			}
			//{RX,RY} = direction vector, normalizedMagnitudeR = magnitude.
			m_RightThumbStickDir.x = normalizedRX * normalizedMagnitudeR;
			m_RightThumbStickDir.y = normalizedRY * normalizedMagnitudeR;
		}
	}

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};
	glm::vec2 m_LeftThumbStickDir{};
	glm::vec2 m_RightThumbStickDir{};

	int m_ControllerIdx{};


};

XInputController::XInputController(int controllerIdx) : m_pImpl(std::make_unique<XInputControllerImpl>(controllerIdx))
{
}

XInputController::~XInputController() = default;


void XInputController::Update()
{
	m_pImpl->Update();
}

bool XInputController::IsDown(Button button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool XInputController::IsUp(Button button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool XInputController::IsPressed(Button button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

const glm::vec2& XInputController::GetLeftThumbDir() const
{
	return m_pImpl->GetLeftThumbDir();
}

const glm::vec2& XInputController::GetRightThumbDir() const
{
	return m_pImpl->GetRightThumbDir();
}

int XInputController::GetControllerIndex() const
{
	return m_pImpl->GetControllerIndex();
}
