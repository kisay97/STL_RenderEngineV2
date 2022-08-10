#include "Core.h"
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
		// 창 생성.
		mainWindow = std::make_unique<Window>(hInstance, width, height, title, WinProc);
		mainWindow->Initialize();

		// 장치 생성.
		deviceManager = std::make_unique<DeviceManager>();
		deviceManager->Initialize(mainWindow->Handle(), mainWindow->Width(), mainWindow->Height());

		// 타이머 생성.
		gameTimer = std::make_unique<GameTimer>();

		app = this;
	}
	
	Application::~Application()
	{
	}
	
	void Application::Initialize()
	{
		// 배경 색상 지정.
		backgroundColor[0] = 0.6f;	// red
		backgroundColor[1] = 0.8f;	// green
		backgroundColor[2] = 0.9f;	// blue
		backgroundColor[3] = 1.0f;	// alpha
	}
	
	void Application::Run()
	{
		// Game Loop.
		Initialize();

		// 타이머 초기화.
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
				// 현재 시간 구하기.
				auto currentTime = gameTimer->Now();

				// 프레임 제한
				if (currentTime >= previousTime + oneFrameTime)
				{
					// 프레임 시간 구하기.
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

		case WM_SIZE:
			// 최소화 확인.
			if (wParam == SIZE_MINIMIZED)
			{
				return 0;
			}

			// 변경된 가로 세로 너비 구하기.
			//uint32 width = static_cast<uint32>(LOWORD(lParam));
			//uint32 height = static_cast<uint32>(HIWORD(lParam));

			// 윈도우에 변경된 가로/세로 크기 설정.
			mainWindow->SetWidthHeight(
				static_cast<uint32>(LOWORD(lParam)), 
				static_cast<uint32>(HIWORD(lParam))
			);

			// 장치 크기 변경 함수 호출.
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

		case WM_KEYDOWN:
		{
			// ESC 키가 눌리면.
			if (wParam == VK_ESCAPE)
			{
				// 메시지 상자 띄우기.
				// 예/아니요 버튼을 제공하는 메시지 상자를 띄우고, "예"를 선택하면 창 삭제.
				if (MessageBox(nullptr, TEXT("Quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
				{
					// 창 핸들 삭제 -> 창 삭제.
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

			ss << mainWindow->Title() << L"    " // 언급 : winapi로 만든 창 제목에 tab은 넣을 수 없음.
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