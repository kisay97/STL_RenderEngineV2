#pragma once

#include <Core/Core.h>

namespace STL 
{
	class ENGINE_API Window
	{
	public:
		Window(HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title,
			WNDPROC procedure);
		~Window();

		// 창 초기화.
		void Initialize();

		// Getter.
		std::wstring Title() const { return title; }
		HINSTANCE Instance() const { return hInstance; }
		HWND Handle() const { return handle; }
		uint32 Width()	const { return width; }
		uint32 Height() const { return height; }

	private:
		std::wstring className;		// 창 등록할 때 사용할 문자열 값.
		std::wstring title;			// 창 제목.
		HINSTANCE hInstance;		// 프로그램 포인터.
		HWND handle;				// 생성된 창을 가리키는 일종의 포인터(핸들).
		uint32 width;				// 창 가로 크기.
		uint32 height;				// 창 세로 크기.
		WNDPROC procedure;			// 창 이벤트 처리 함수 포인터.
	};
}