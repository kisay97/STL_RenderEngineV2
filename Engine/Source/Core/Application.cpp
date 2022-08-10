#include "Core.h"
#include "Application.h"
#include <Device/KeyboardInput.h>
#include <Device/MouseInput.h>

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

		// Ÿ�̸� ����.
		gameTimer = std::make_unique<GameTimer>();

		// Ű����/���콺 ����.
		keyboard = std::make_unique<KeyboardInput>();
		keyboard->Initialize();

		mouse = std::make_unique<MouseInput>(mainWindow->Handle());
		mouse->Initialize();

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

		// Ÿ�̸� �ʱ�ȭ.
		gameTimer->Reset();

		auto previousTime = gameTimer->Now();
		auto oneFrameTime = gameTimer->ClockFrequency() / targetFrameRate;

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
				// ���� �ð� ���ϱ�.
				auto currentTime = gameTimer->Now();

				// ������ ����
				if (currentTime >= previousTime + oneFrameTime)
				{
					// ������ �ð� ���ϱ�.
					gameTimer->Tick();

					CalculateFrameStatistics();
					ProcessInput();
					Update(gameTimer->DeltaTime());
					Draw();

					previousTime = currentTime;
				}
			}
		}
	}
	
	void Application::ProcessInput()
	{
		keyboard->Update();
		mouse->Update();
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

		case WM_ACTIVATEAPP:
			DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
			DirectX::Mouse::ProcessMessage(message, wParam, lParam);
			return 0;

		case WM_SIZE:
			// �ּ�ȭ Ȯ��.
			if (wParam == SIZE_MINIMIZED)
			{
				return 0;
			}

			// ����� ���� ���� �ʺ� ���ϱ�.
			//uint32 width = static_cast<uint32>(LOWORD(lParam));
			//uint32 height = static_cast<uint32>(HIWORD(lParam));

			// �����쿡 ����� ����/���� ũ�� ����.
			mainWindow->SetWidthHeight(
				static_cast<uint32>(LOWORD(lParam)), 
				static_cast<uint32>(HIWORD(lParam))
			);

			// ��ġ ũ�� ���� �Լ� ȣ��.
			OnResize();

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

		// Ű���� �Է�.
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYUP:
			DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
			return 0;
		// ���콺 �Է�.
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHOVER:
			DirectX::Mouse::ProcessMessage(message, wParam, lParam);
			return 0;
		}

		return DefWindowProc(handle, message, wParam, lParam);
	}

	KeyboardInput* Application::GetKeyboard()
	{
		return keyboard.get();
	}

	MouseInput* Application::GetMouse()
	{
		return mouse.get();
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
		deviceManager->EndScene(0, 0);
	}

	void Application::OnResize()
	{
		deviceManager->OnResize(
			mainWindow->Width(),
			mainWindow->Height()
		);
	}

	void Application::CalculateFrameStatistics()
	{
		static int frameCount = 0;
		static float elapsedTime = 0.0f;

		++frameCount;

		auto totalTime = gameTimer->TotalTime();

		if ((gameTimer->TotalTime() - elapsedTime) >= 1.0f)
		{
			float framePerSecond = static_cast<float>(frameCount);
			float millisecondsPerFrame = 1000.0f / framePerSecond;

			std::wstringstream ss;

			ss << mainWindow->Title() << L"    " // ��� : winapi�� ���� â ���� tab�� ���� �� ����.
				<< L"FPS: " << framePerSecond << "    "
				<< L"Frame Time: " << millisecondsPerFrame << L" (ms)"
				<< L"    Width: " << mainWindow->Width()
				<< L", Height: " << mainWindow->Height();

			mainWindow->SetTitle(ss.str());

			frameCount = 0;
			elapsedTime += 1.0f;
		}
	}
}