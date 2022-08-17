#include "Core.h"
#include "MouseInput.h"

namespace STL
{
	using namespace DirectX;

	std::unique_ptr<DirectX::Mouse> MouseInput::mouse(new DirectX::Mouse());

	MouseInput::~MouseInput()
	{
	}

	MouseInput::MouseInput(HWND windowHandle, MouseMode mode)
	{
		mouse->SetWindow(windowHandle);
		SetMode(mode);
	}

	Mouse* MouseInput::Mouse()
	{
		return mouse.get();
	}

	const Mouse::State& MouseInput::CurrentState() const
	{
		return currentState;
	}

	const Mouse::State& MouseInput::PreviousState() const
	{
		return previousState;
	}

	void MouseInput::Initialize()
	{
		currentState = mouse->GetState();
		previousState = currentState;
	}

	void MouseInput::Update()
	{
		previousState = currentState;
		currentState = mouse->GetState();
	}

	void MouseInput::SetWindow(HWND window)
	{
		mouse->SetWindow(window);
	}

	int MouseInput::X() const
	{
		return currentState.x;
	}

	int MouseInput::DeltaX() const
	{
		if (Mode() == MouseMode::Relative)
		{
			return X();
		}
		else
		{
			return currentState.x - previousState.x;
		}
	}

	int MouseInput::Y() const
	{
		return currentState.y;
	}

	int MouseInput::DeltaY() const
	{
		if (Mode() == MouseMode::Relative)
		{
			return Y();
		}
		else
		{
			return currentState.y - previousState.y;
		}
	}

	int MouseInput::Wheel() const
	{
		return currentState.scrollWheelValue;
	}

	bool MouseInput::IsWheelUp() const
	{
		return currentState.scrollWheelValue > previousState.scrollWheelValue;
	}

	bool MouseInput::IsWheelDown() const
	{
		return currentState.scrollWheelValue < previousState.scrollWheelValue;
	}

	bool MouseInput::IsButtonUp(MouseButtons button) const
	{
		return GetButtonState(currentState, button) == false;
	}

	bool MouseInput::IsButtonDown(MouseButtons button) const
	{
		return GetButtonState(currentState, button);
	}

	bool MouseInput::WasButtonUp(MouseButtons button) const
	{
		return GetButtonState(previousState, button) == false;
	}

	bool MouseInput::WasButtonDown(MouseButtons button) const
	{
		return GetButtonState(previousState, button);
	}

	bool MouseInput::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return IsButtonDown(button) && WasButtonUp(button);
	}

	bool MouseInput::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return IsButtonUp(button) && WasButtonDown(button);
	}

	bool MouseInput::IsButtonHeldDown(MouseButtons button) const
	{
		return IsButtonDown(button) && WasButtonDown(button);
	}

	MouseMode MouseInput::Mode() const
	{
		auto state = mouse->GetState();
		return static_cast<MouseMode>(state.positionMode);
	}

	void MouseInput::SetMode(MouseMode mode)
	{
		mouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	bool MouseInput::GetButtonState(const DirectX::Mouse::State& state, MouseButtons button) const
	{
		switch (button)
		{
		case MouseButtons::Left:
			return state.leftButton;

		case MouseButtons::Right:
			return state.rightButton;

		case MouseButtons::Middle:
			return state.middleButton;

		case MouseButtons::X1:
			return state.xButton1;

		case MouseButtons::X2:
			return state.xButton2;

		default:
			throw std::exception("Invalid MouseButtons");
		}
	}
}