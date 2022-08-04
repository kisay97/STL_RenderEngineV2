#pragma once

#include <Core/Core.h>

namespace STL
{
	class Quaternionf;

	class ENGINE_API Vector3f
	{
	public:
		float x;
		float y;
		float z;

		static const Vector3f Zero;
		static const Vector3f One;
		
		static const Vector3f Right;
		static const Vector3f Up;
		static const Vector3f Forward;

		Vector3f() 
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vector3f(float x, float y, float z) 
			: x(x), y(y), z(z) 
		{
		}

		Vector3f(const Vector3f& other)
			: x(other.x), y(other.y), z(other.z)
		{
		}

		~Vector3f() = default;

		std::wstring ToString();

		float Length();
		float Dot(const Vector3f& other);
		Vector3f Normalized();
		Vector3f Cross(const Vector3f& other);

		Quaternionf ToQuaternion();

		bool Equal(Vector3f other);

		Vector3f& operator=(const Vector3f& other);

		Vector3f operator+(const Vector3f& other);
		Vector3f operator+(const float& other);
		Vector3f& operator+=(const Vector3f& other);
		Vector3f& operator+=(const float& other);

		Vector3f operator-(const Vector3f& other);
		Vector3f operator-(const float& other);
		Vector3f& operator-=(const Vector3f& other);
		Vector3f& operator-=(const float& other);

		Vector3f operator*(const Vector3f& other);
		Vector3f operator*(const float& other);
		Vector3f& operator*=(const Vector3f& other);
		Vector3f& operator*=(const float& other);

		Vector3f operator/(const Vector3f& other);
		Vector3f operator/(const float& other);
		Vector3f& operator/=(const Vector3f& other);
		Vector3f& operator/=(const float& other);

		bool operator==(Vector3f other);
		bool operator!=(Vector3f other);
	};
}