#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Vector3f
	{
	public:
		float x;
		float y;
		float z;

		Vector3f()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vector3f(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}
	};
}