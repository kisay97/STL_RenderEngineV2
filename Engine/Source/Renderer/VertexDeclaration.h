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
			texCoord(uv.x, uv.y)
		{
		}
	};

	struct ENGINE_API VertexPositionColorUVNormalTangentBinormal
	{
		Vector3f position;
		Vector3f color;
		Vector2f texCoord;
		Vector3f normal;
		Vector3f binormal;
		Vector3f tangent;

		VertexPositionColorUVNormalTangentBinormal()
			: position(), color(), texCoord(), normal(), binormal(), tangent()
		{
		}

		VertexPositionColorUVNormalTangentBinormal(
			float x, float y, float z,
			float r, float g, float b,
			float u, float v,
			float nx, float ny, float nz,
			float bx, float by, float bz,
			float tx, float ty, float tz)
			: position(x, y, z), color(r, g, b), 
			texCoord(u, v), normal(nx, ny, nz),
			binormal(bx, by, bz), tangent(tx, ty, tz)
		{
		}

		VertexPositionColorUVNormalTangentBinormal(
			const Vector3f& position,
			const Vector3f& color,
			const Vector2f& uv,
			const Vector3f& normal,
			const Vector3f& binormal,
			const Vector3f& tangent)
			: position(position), color(color), texCoord(uv), 
			normal(normal), binormal(binormal), tangent(tangent)
		{
		}
	};

	struct ENGINE_API VertexPositionColorUVNormal
	{
		Vector3f position;
		Vector3f color;
		Vector2f texCoord;
		Vector3f normal;

		VertexPositionColorUVNormal()
			: position(), color(), texCoord(), normal()
		{
		}

		VertexPositionColorUVNormal(
			float x, float y, float z,
			float r, float g, float b,
			float u, float v,
			float nx, float ny, float nz)
			: position(x, y, z), color(r, g, b), texCoord(u, v), normal(nx, ny, nz)
		{
		}

		VertexPositionColorUVNormal(
			const Vector3f& position,
			const Vector3f& color,
			const Vector2f& uv,
			const Vector3f& normal)
			: position(position), color(color), texCoord(uv), normal(normal)
		{
		}
	};

	struct ENGINE_API VertexPositionUV
	{
		Vector3f position;
		Vector2f texCoord;

		VertexPositionUV()
			: position(), texCoord()
		{
		}

		VertexPositionUV(
			float x, float y, float z,
			float u, float v)
			: position(x, y, z), texCoord(u, v)
		{
		}

		VertexPositionUV(
			const Vector3f& position,
			const Vector2f& uv)
			: position(position.x, position.y, position.z),
			texCoord(uv.x, uv.y)
		{
		}
	};
}