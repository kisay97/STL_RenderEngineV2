#include "Application.h"

namespace STL
{
	Application* app = nullptr;

	LRESULT CALLBACK WinProc(HWND handle, uint32 message, WPARAM wParam, LPARAM lParam)
	{
		if (app == nullptr)
		{
			return DefWindowProc(handle, message, wParam, lParam);
		}

		return app->MessageProcessor(handle, message, wParam, lParam);
	}

	Application::Application(HINSTANCE hInstance, uint32 width, uint32 height, const std::wstring& title)
	{
		// â ����.
		mainWindow = std::make_unique<Window>(hInstance, width, height, title, WinProc);
		mainWindow->Initialize();

		// ��ġ ����.
		deviceManager = std::make_unique<DeviceManager>();
		deviceManager->Initialize(mainWindow->Handle(), mainWindow->Width(), mainWindow->Height());

		app = this;
	}
	
	Application::~Application()
	{
	}
	
	void Application::Initialize()
	{
		// ��� ���� ����.
		backgroundColor[0] = 0.6f;	// red
		backgroundColor[1] = 0.8f;	// green
		backgroundColor[2] = 0.9f;	// blue
		backgroundColor[3] = 1.0f;	// alpha
	}
	
	void Application::Run()
	{
		// Game Loop.
		Initialize();

		MSG msg = {};
		while (msg.message != WM_QUIT) 
		{
			if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				ProcessInput();
				Update();
				Draw();
			}
		}
	}
	
	void Application::ProcessInput()
	{
	}
	
	void Application::Update(float deltaTime)
	{
	}
	
	void Application::Draw()
	{
		BeginScene();
		RenderScene();
		EndScene();
	}
	
	LRESULT Application::MessageProcessor(HWND handle, uint32 message, WPARAM wParam, LPARAM lParam)
	{

		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(handle, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(handle, &ps);
		}
		return 0;

		case WM_KEYDOWN:
		{
			// ESC Ű�� ������.
			if (wParam == VK_ESCAPE)
			{
				// �޽��� ���� ����.
				// ��/�ƴϿ� ��ư�� �����ϴ� �޽��� ���ڸ� ����, "��"�� �����ϸ� â ����.
				if (MessageBox(nullptr, TEXT("Quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
				{
					// â �ڵ� ���� -> â ����.
					DestroyWindow(handle);
				}
			}
		}
		return 0;
		}

		return DefWindowProc(handle, message, wParam, lParam);
	}
	
	void Application::BeginScene()
	{
		deviceManager->BeginScene(backgroundColor);
	}
	
	void Application::RenderScene()
	{
		deviceManager->RenderScene();
	}
	
	void Application::EndScene()
	{
		deviceManager->EndScene(1, 0);
	}
}