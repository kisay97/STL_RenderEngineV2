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

		// â �ʱ�ȭ.
		void Initialize();

		// Getter.
		std::wstring Title() const { return title; }
		HINSTANCE Instance() const { return hInstance; }
		HWND Handle() const { return handle; }
		uint32 Width()	const { return width; }
		uint32 Height() const { return height; }

	private:
		std::wstring className;		// â ����� �� ����� ���ڿ� ��.
		std::wstring title;			// â ����.
		HINSTANCE hInstance;		// ���α׷� ������.
		HWND handle;				// ������ â�� ����Ű�� ������ ������(�ڵ�).
		uint32 width;				// â ���� ũ��.
		uint32 height;				// â ���� ũ��.
		WNDPROC procedure;			// â �̺�Ʈ ó�� �Լ� ������.
	};
}