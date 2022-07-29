#pragma once

#include <Core/Core.h>
#include <Math/Vector3f.h>
#include <Math/Vector2f.h>

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

	struct ENGINE_API VertexPositionColor
	{
		Vector3f position;
		Vector3f color;

		VertexPositionColor()
			: position(), color()
		{
		}

		VertexPositionColor(
			float x, float y, float z,
			float r, float g, float b)
			: position(x, y, z), color(r, g, b)
		{
		}

		VertexPositionColor(
			const Vector3f& position,
			const Vector3f& color)
			: position(position.x, position.y, position.z),
			color(color.x, color.y, color.z)
		{
		}
	};

	struct ENGINE_API VertexPositionColorUV
	{
		Vector3f position;
		Vector3f color;
		Vector2f texCoord;

		VertexPositionColorUV()
			: position(), color(), texCoord()
		{
		}

		VertexPositionColorUV(
			float x, float y, float z,
			float r, float g, float b,
			float u, float v)
			: position(x, y, z), color(r, g, b), texCoord(u, v)
		{
		}

		VertexPositionColorUV(
			const Vector3f& position,
			const Vector3f& color,
			const Vector2f& uv)
			: position(position.x, position.y, position.z),
			color(color.x, color.y, color.z),
			texCoord(uv.u, uv.v)
		{
		}
	};
}