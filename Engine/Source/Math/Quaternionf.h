#pragma once

#include <Core/Core.h>

namespace STL
{
	class Vector3f;
	class Matrix4f;

	
	class alignas(16) ENGINE_API Quaternionf
	{
	public:
		float x, y, z, w;

		Quaternionf();
		Quaternionf(float x, float y, float z, float w);

		Quaternionf Normalized();
		float Dot(const Quaternionf& other);

		float Magnitude();
		Quaternionf Conjugate();
		Quaternionf Inverse();

		Vector3f ToEuler();
		Matrix4f ToMatrix4f();

		Vector3f RotateVector(const Vector3f& vector);

		Quaternionf operator=(const Quaternionf& other);

		Quaternionf operator+(const Quaternionf& other);
		Quaternionf operator+(const float s);
		Quaternionf& operator+=(const Quaternionf& other);
		Quaternionf& operator+=(const float s);

		Quaternionf operator-(const Quaternionf& other);
		Quaternionf operator-(const float s);
		Quaternionf& operator-=(const Quaternionf& other);
		Quaternionf& operator-=(const float s);

		Quaternionf operator*(const Quaternionf& other);
		Quaternionf operator*(const float s);
		Quaternionf& operator*=(const Quaternionf& other);
		Quaternionf& operator*=(const float s);

		Quaternionf operator/(const Quaternionf& other);
		Quaternionf operator/(const float s);
		Quaternionf& operator/=(const Quaternionf& other);
		Quaternionf& operator/=(const float s);

		static Quaternionf Identity() { return Quaternionf(0.0f, 0.0f, 0.0f, 1.0f); }
	};
}