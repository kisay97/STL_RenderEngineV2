#pragma once

#include <Core/Core.h>
#include <Device/Window.h>
#include <Device/DeviceManager.h>
#include <Device/GameTimer.h>

namespace STL 
{
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

		virtual LRESULT MessageProcessor(
			HWND handle,
			uint32 message,
			WPARAM wParam,
			LPARAM lParam
		);

	protected:

		void CalculateFrameStatistics();
		virtual void BeginScene();
		virtual void RenderScene();
		virtual void EndScene();
		
		std::unique_ptr<Window> mainWindow;
		std::unique_ptr<DeviceManager> deviceManager;

		std::unique_ptr<GameTimer> gameTimer;
		uint32 targetFrameRate = 120;

		float backgroundColor[4];
	};
}