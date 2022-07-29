#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Vector2f
	{
	public:
		float u;
		float v;

		Vector2f()
			: u(0.0f), v(0.0f)
		{
		}

		Vector2f(float u, float v)
			: u(u), v(v)
		{
		}
	};
}