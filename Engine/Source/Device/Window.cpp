#include "Window.h"
#include <exception>        // 표준 예외(exception).

namespace STL
{
	Window::Window(
		HINSTANCE hInstance, 
		uint32 width, 
		uint32 height, 
		const std::wstring& title, 
		WNDPROC procedure)
		: hInstance(hInstance),
		width(width), height(height),
		title(title), className(L"Engine Window Class"),
		procedure(procedure),
		handle(nullptr)
	{
	}
	Window::~Window()
	{
		// 창 등록 해제.
		UnregisterClass(className.c_str(), hInstance);
	}
	void Window::Initialize()
	{
        // 창 클래스 설정 및 생성.
        WNDCLASS wc = { };

        // Invoke.
        wc.lpfnWndProc = procedure;    // 콜백(Callback) / 위임(Delegate).
        wc.hInstance = hInstance;
        wc.lpszClassName = className.c_str();

        // 창 클래스 이름 등록.
        RegisterClass(&wc);

        // Create the window.

        // 창 크기 조정.
        // RECT는 직사각형 구조체, (left, top, right, bottom).
        RECT rect = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        // 조정된 직사각형 크기로 창 가로/세로 크기 구하기.
        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        // 화면 중심에서 창을 그리기 위한 생성좌표 구하기.
        // GetSystemMetrics(SM_CXSCREEN) -> 모니터 가로 크기 구하는 함수.
        // GetSystemMetrics(SM_CYSCREEN) -> 모니터 세로 크기 구하는 함수.
        int xPosition = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
        int yPosition = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

        handle = CreateWindowEx(
            0,                              // Optional window styles.
            className.c_str(),              // Window class
            title.c_str(),                  // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            xPosition, yPosition, windowWidth, windowHeight,

            nullptr,        // Parent window    
            nullptr,        // Menu
            hInstance,      // Instance handle
            nullptr         // Additional application data
        );

        if (handle == nullptr)
        {
            throw std::exception("윈도우 생성 실패.");
        }

        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);
	}
}