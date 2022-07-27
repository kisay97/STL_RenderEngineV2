#pragma once

#include<Core/Core.h>
#include<exception>

namespace STL
{
	// 인라인 규칙.
	// Inline은 함수 안에 있는 코드를 그대로 함수 호출 위치에 복사/붙여넣기 하는 방식.
	// 기존 함수 호출 방식은 스택 메모리에 함수 코드를 올려놓고 실행하기 때문에
	// 인라인을 했을 때 성능상 이점이 있을 수 있다.

	// 일단 inline은 컴파일러가 할지 말지 결정함. (아래는 일반적인 사항.)
	// 1. 함수 내 코드가 7줄 이하
	// 2. 재귀 호출 없음.
	inline void ThrowIfFailed(HRESULT hr, const char* message)
	{
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, message, "Error", MB_OK);
			std::exception(message);
		}
	}
}