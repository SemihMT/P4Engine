#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{


	class XInputController final
	{
		

	public:
		XInputController(int controllerIdx);
		~XInputController();

		XInputController(const XInputController& other) = delete;
		XInputController(XInputController&& other) = delete;
		XInputController& operator=(const XInputController& other) = delete;
		XInputController& operator=(XInputController&& other) = delete;

		enum class Button
		{
			DPAD_UP = 0x0001,
			DPAD_DOWN = 0x0002,
			DPAD_LEFT = 0x0004,
			DPAD_RIGHT = 0x0008,
			START = 0x0010,
			BACK = 0x0020,
			LEFT_THUMB = 0x0040,
			RIGHT_THUMB = 0x0080,
			LEFT_SHOULDER = 0x0100,
			RIGHT_SHOULDER = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000

		};

		void Update();

		bool IsDown(Button button) const;
		bool IsUp(Button button) const;
		bool IsPressed(Button button) const;
		const glm::vec2& GetLeftThumbDir() const;
		const glm::vec2& GetRightThumbDir() const;
		int GetControllerIndex() const;

	private:
		//Pointer to Implementation (PIMPL idiom)
		class XInputControllerImpl;
		std::unique_ptr<XInputControllerImpl> m_pImpl{};
	};

}
