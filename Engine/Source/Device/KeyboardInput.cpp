#include "Core.h"
#include "KeyboardInput.h"

namespace STL
{
	using namespace DirectX;

	std::unique_ptr<Keyboard> KeyboardInput::keyboard(new DirectX::Keyboard());

	KeyboardInput::KeyboardInput()
		: currentState(), previousState()
	{
	}

	KeyboardInput::~KeyboardInput()
	{
	}

	DirectX::Keyboard* KeyboardInput::Keyboard()
	{
		return keyboard.get();
	}

	const DirectX::Keyboard::State& KeyboardInput::CurrentState() const
	{
		return currentState;
	}

	const DirectX::Keyboard::State& KeyboardInput::PreviousState() const
	{
		return previousState;
	}

	void KeyboardInput::Initialize()
	{
		currentState = keyboard->GetState();
		previousState = currentState;
	}

	void KeyboardInput::Update()
	{
		previousState = currentState;
		currentState = keyboard->GetState();
	}

	bool KeyboardInput::IsKeyUp(Keys key) const
	{
		return currentState.IsKeyUp(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardInput::IsKeyDown(Keys key) const
	{
		return currentState.IsKeyDown(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardInput::WasKeyUp(Keys key) const
	{
		return previousState.IsKeyUp(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardInput::WasKeyDown(Keys key) const
	{
		return previousState.IsKeyDown(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardInput::WasKeyPressedThisFrame(Keys key) const
	{
		return IsKeyDown(key) && WasKeyUp(key);
	}

	bool KeyboardInput::WasKeyReleasedThisFrame(Keys key) const
	{
		return IsKeyUp(key) && WasKeyDown(key);
	}

	bool KeyboardInput::IsKeyHeldDown(Keys key) const
	{
		return IsKeyDown(key) && WasKeyDown(key);
	}
}