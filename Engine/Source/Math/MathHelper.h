#pragma once

#include <Core/Core.h>

namespace STL
{
	namespace MathHelper
	{
		constexpr float PI = 3.14159265f;
		constexpr float Deg2Rad = (PI / 180.0f);
		constexpr float Rad2Deg = (180.0f / PI);
		ENGINE_API float Lerpf(float a, float b, float alpha);
	};
}