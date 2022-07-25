#include "Window.h"
#include <exception>        // ǥ�� ����(exception).

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
		// â ��� ����.
		UnregisterClass(className.c_str(), hInstance);
	}
	void Window::Initialize()
	{
        // â Ŭ���� ���� �� ����.
        WNDCLASS wc = { };

        // Invoke.
        wc.lpfnWndProc = procedure;    // �ݹ�(Callback) / ����(Delegate).
        wc.hInstance = hInstance;
        wc.lpszClassName = className.c_str();

        // â Ŭ���� �̸� ���.
        RegisterClass(&wc);

        // Create the window.

        // â ũ�� ����.
        // RECT�� ���簢�� ����ü, (left, top, right, bottom).
        RECT rect = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        // ������ ���簢�� ũ��� â ����/���� ũ�� ���ϱ�.
        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        // ȭ�� �߽ɿ��� â�� �׸��� ���� ������ǥ ���ϱ�.
        // GetSystemMetrics(SM_CXSCREEN) -> ����� ���� ũ�� ���ϴ� �Լ�.
        // GetSystemMetrics(SM_CYSCREEN) -> ����� ���� ũ�� ���ϴ� �Լ�.
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
            throw std::exception("������ ���� ����.");
        }

        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);
	}
}