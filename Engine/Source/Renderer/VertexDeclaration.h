#pragma once

#include <Core/Core.h>
#include <Math/Vector3f.h>

namespace STL
{
	struct ENGINE_API VertexPosition
	{
		Vector3f position;

		VertexPosition()
			: position()
		{
		}

		VertexPosition(float x, float y, float z)
			: position(x, y, z)
		{
		}

		VertexPosition(const Vector3f& position)
			: position(position.x, position.y, position.z)
		{
		}
	};
}