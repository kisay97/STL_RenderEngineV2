#pragma once

#include <Core/Core.h>
#include <Mouse.h>

namespace STL
{
	enum class MouseButtons
	{
		Left = 0,
		Right,
		Middle,
		X1,
		X2
	};

	enum class MouseMode
	{
		Absolute = 0,
		Relative
	};

	class ENGINE_API MouseInput
	{
	public:
		MouseInput(HWND handle, MouseMode mode = MouseMode::Relative);
		~MouseInput();

		static DirectX::Mouse* Mouse();

		const DirectX::Mouse::State& CurrentState() const;
		const DirectX::Mouse::State& PreviousState() const;

		virtual void Initialize();
		virtual void Update();
		void SetWindow(HWND handle);

		int X() const;
		int DeltaX() const;

		int Y() const;
		int DeltaY() const;
		int Wheel() const;

		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;
		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;
		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;
		bool IsButtonHeldDown(MouseButtons button) const;

		MouseMode Mode() const;
		void SetMode(MouseMode mode);

	private:

		bool GetButtonState(const DirectX::Mouse::State& state, MouseButtons button) const;

		static std::unique_ptr<DirectX::Mouse> mouse;

		DirectX::Mouse::State currentState;
		DirectX::Mouse::State previousState;
	};
}