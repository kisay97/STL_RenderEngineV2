#pragma once

#include <Core/Core.h>
#include <Device/Window.h>
#include <Device/DeviceManager.h>
#include <Device/GameTimer.h>

namespace STL 
{
	// 전방선언.
	class KeyboardInput;
	class MouseInput;

	class ENGINE_API Application
	{
	public:
		Application(
			HINSTANCE hInstance, 
			uint32 width, 
			uint32 height, 
			const std::wstring& title
		);

		virtual ~Application();

		virtual void Initialize();
		virtual void Run();

		virtual void ProcessInput();
		virtual void Update(float deltaTime = 0.0f);
		virtual void Draw();

		uint32 Width() { return mainWindow->Width(); }
		uint32 Height() { return mainWindow->Height(); }

		virtual LRESULT MessageProcessor(
			HWND handle,
			uint32 message,
			WPARAM wParam,
			LPARAM lParam
		);

		KeyboardInput* GetKeyboard();
		MouseInput* GetMouse();

	protected:

		void CalculateFrameStatistics();
		virtual void BeginScene();
		virtual void RenderScene();
		virtual void EndScene();
		virtual void OnResize();
		
		std::unique_ptr<Window> mainWindow;
		std::unique_ptr<DeviceManager> deviceManager;

		std::unique_ptr<KeyboardInput> keyboard;
		std::unique_ptr<MouseInput> mouse;

		std::unique_ptr<GameTimer> gameTimer;
		uint32 targetFrameRate = 120;

		float backgroundColor[4];
	};
}