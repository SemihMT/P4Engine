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
		//Find out whether the controller is connected
		m_IsConnected = CheckForConnection();

		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));


	}

	
	bool CheckForConnection() const
	{
		XINPUT_STATE tmpState{};
		const DWORD dwResult = XInputGetState(m_ControllerIdx, &tmpState); //can tmpState be nullptr to save memory?
		if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
		{
#ifdef _DEBUG
			printf_s("Controller not connected!\n");
#endif
			return false;
		}
		return true;
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
			printf_s("Controller not connected!\n");
			m_IsConnected = false;

		}
		if (dwResult == ERROR_SUCCESS)
		{
			m_IsConnected = true;
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
	const glm::vec2 GetLeftThumbDir() const
	{
		return m_LeftThumbStickDir;
	}
	const glm::vec2 GetRightThumbDir() const
	{
		return m_RightThumbStickDir;
	}
	int GetControllerIndex() const
	{
		return m_ControllerIdx;
	}
	bool IsConnected() const
	{
		return m_IsConnected;
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

			// Check if magnitudeL is greater than 0 before normalization
			const float normalizedLX = (magnitudeL > 0) ? LX / magnitudeL : 0;
			const float normalizedLY = (magnitudeL > 0) ? LY / magnitudeL : 0;

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


			// Check if magnitudeL is greater than 0 before normalization
			const float normalizedRX = (magnitudeR > 0) ? RX / magnitudeR : 0;
			const float normalizedRY = (magnitudeR > 0) ? RY / magnitudeR : 0;

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
	bool m_IsConnected{ false };


};

XInputController::XInputController(int controllerIdx) : m_pImpl(std::make_unique<XInputControllerImpl>(controllerIdx))
{
}

XInputController::~XInputController() = default;

bool XInputController::IsConnected() const
{
	return m_pImpl->IsConnected();
}

bool XInputController::CheckForConnection() const
{
	return m_pImpl->CheckForConnection();
}


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

const glm::vec2 XInputController::GetLeftThumbDir() const
{
	return m_pImpl->GetLeftThumbDir();
}

const glm::vec2 XInputController::GetRightThumbDir() const
{
	return m_pImpl->GetRightThumbDir();
}

int XInputController::GetControllerIndex() const
{
	return m_pImpl->GetControllerIndex();
}
