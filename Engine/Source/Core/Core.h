#pragma once

// 유니코드 설정.
#ifndef UNICODE
#define UNICODE
#endif

// 미봉책. (DLL 뽑는 코드에 STL 쓰면 4251 워닝나는데, 문제될 게 없으므로 Warning을 꺼버린다.)
// 정석대로 할려면 https://mgun.tistory.com/681 참고
#pragma warning(disable:4251)
#pragma warning(disable:4244)
#pragma warning(disable:4172)

#ifdef ENGINE_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

// includes.
#include <Windows.h>
#include <d3d11.h>			// dx11
#include <d3dcompiler.h>	// 쉐이더 컴파일/로드
#include <comdef.h>

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>			// smart pointer.
#include <algorithm>
#include <sstream>			// 문자열 조합에 편리함.
#include <filesystem>

#include <cassert>			// assert 함수 사용을 위함. 특정 조건을 만족하지 않으면 중단.

// 타입 재정의.
using uint32 = unsigned int;
using uint64 = unsigned __int64;
using int64 = __int64;
using uint8 = unsigned char;

// 편의 함수.
// COM 객체 메모리 해제할 때 사용할 함수.
// 따라서 Type에는 COM 타입에 객체만 허용됨.
template<typename Type>
void SafeRelease(Type t)
{
	if (t != nullptr)
	{
		t->Release();
		t = nullptr;
	}
}