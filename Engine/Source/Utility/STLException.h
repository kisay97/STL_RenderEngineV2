#pragma once

#include<Core/Core.h>
#include<exception>

namespace STL
{
	// �ζ��� ��Ģ.
	// Inline�� �Լ� �ȿ� �ִ� �ڵ带 �״�� �Լ� ȣ�� ��ġ�� ����/�ٿ��ֱ� �ϴ� ���.
	// ���� �Լ� ȣ�� ����� ���� �޸𸮿� �Լ� �ڵ带 �÷����� �����ϱ� ������
	// �ζ����� ���� �� ���ɻ� ������ ���� �� �ִ�.

	// �ϴ� inline�� �����Ϸ��� ���� ���� ������. (�Ʒ��� �Ϲ����� ����.)
	// 1. �Լ� �� �ڵ尡 7�� ����
	// 2. ��� ȣ�� ����.
	inline void ThrowIfFailed(HRESULT hr, const char* message)
	{
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, message, "Error", MB_OK);
			std::exception(message);
		}
	}
}