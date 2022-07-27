#pragma once

// �����ڵ� ����.
#ifndef UNICODE
#define UNICODE
#endif

// �̺�å. (DLL �̴� �ڵ忡 STL ���� 4251 ���׳��µ�, ������ �� �����Ƿ� Warning�� ��������.)
// ������� �ҷ��� https://mgun.tistory.com/681 ����
#pragma warning(default:4251)

#ifdef ENGINE_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

// includes.
#include <Windows.h>
#include <d3d11.h>			// dx11
#include <d3dcompiler.h>	// ���̴� ������/�ε�
#include <comdef.h>

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>			// smart pointer.
#include <algorithm>
#include <sstream>			// ���ڿ� ���տ� ����.
#include <filesystem>

// Ÿ�� ������.
using uint32 = unsigned int;
using uint64 = unsigned __int64;
using int64 = __int64;

// ���� �Լ�.
// COM ��ü �޸� ������ �� ����� �Լ�.
// ���� Type���� COM Ÿ�Կ� ��ü�� ����.
template<typename Type>
void SafeRelease(Type t)
{
	if (t != nullptr)
	{
		t->Release();
		t = nullptr;
	}
}