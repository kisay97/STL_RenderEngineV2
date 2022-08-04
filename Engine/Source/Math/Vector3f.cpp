#include <Core.h>
#include "Vector3f.h"
#include "MathHelper.h"
#include "Quaternionf.h"
#include <sstream>

namespace STL
{
	const Vector3f Vector3f::Zero = { 0.0f, 0.0f, 0.0f };
	const Vector3f Vector3f::One = { 1.0f, 1.0f, 1.0f };
	
	const Vector3f Vector3f::Right = { 1.0f, 0.0f, 0.0f };
	const Vector3f Vector3f::Up = { 0.0f, 1.0f, 0.0f };
	const Vector3f Vector3f::Forward = { 0.0f, 0.0f, 1.0f };

	std::wstring Vector3f::ToString()
	{
		std::wstringstream stream;
		stream << "(" << x << ", " << y << ", " << z << ")";

		return stream.str();
	}

	float Vector3f::Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	float Vector3f::Dot(const Vector3f& other)
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	Vector3f Vector3f::Normalized()
	{
		float length = Length();
		float _x = x / length;
		float _y = y / length;
		float _z = z / length;

		return Vector3f(_x, _y, _z);
	}

	Vector3f Vector3f::Cross(const Vector3f& other)
	{
		float _x = y * other.z - z * other.y;
		float _y = -x * other.z + z * other.x;
		float _z = x * other.y - y * other.x;

		return Vector3f(_x, _y, _z);
	}

	Quaternionf Vector3f::ToQuaternion()
	{
		float cosX = (std::cosf(x * MathHelper::Deg2Rad * 0.5f));
		float sinX = (std::sinf(x * MathHelper::Deg2Rad * 0.5f));

		float cosY = (std::cosf(y * MathHelper::Deg2Rad * 0.5f));
		float sinY = (std::sinf(y * MathHelper::Deg2Rad * 0.5f));

		float cosZ = (std::cosf(z * MathHelper::Deg2Rad * 0.5f));
		float sinZ = (std::sinf(z * MathHelper::Deg2Rad * 0.5f));

		Quaternionf res;
		Quaternionf qX(sinX, 0.0f, 0.0f, cosX);
		Quaternionf qY(0.0f, sinY, 0.0f, cosY);
		Quaternionf qZ(0.0f, 0.0f, sinZ, cosZ);

		//res = (qY * qX) * qZ;
		res = (qX * qY) * qZ;
		return res;
	}

	bool Vector3f::Equal(Vector3f other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	Vector3f& Vector3f::operator=(const Vector3f& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3f Vector3f::operator+(const Vector3f& other)
	{
		return Vector3f(x + other.x, y + other.y, z + other.z);
	}

	Vector3f Vector3f::operator+(const float& other)
	{
		return Vector3f(x + other, y + other, z + other);
	}

	Vector3f& Vector3f::operator+=(const Vector3f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vector3f& Vector3f::operator+=(const float& other)
	{
		x += other;
		y += other;
		z += other;

		return *this;
	}

	Vector3f Vector3f::operator-(const Vector3f& other)
	{
		return Vector3f(x - other.x, y - other.y, z - other.z);
	}

	Vector3f Vector3f::operator-(const float& other)
	{
		return Vector3f(x - other, y - other, z - other);
	}

	Vector3f& Vector3f::operator-=(const Vector3f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vector3f& Vector3f::operator-=(const float& other)
	{
		x -= other;
		y -= other;
		z -= other;

		return *this;
	}

	Vector3f Vector3f::operator*(const Vector3f& other)
	{
		return Vector3f(x * other.x, y * other.y, z * other.z);
	}

	Vector3f Vector3f::operator*(const float& other)
	{
		return Vector3f(x * other, y * other, z * other);
	}

	Vector3f& Vector3f::operator*=(const Vector3f& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vector3f& Vector3f::operator*=(const float& other)
	{
		x *= other;
		y *= other;
		z *= other;

		return *this;
	}

	Vector3f Vector3f::operator/(const Vector3f& other)
	{
		return Vector3f(x / other.x, y / other.y, z / other.z);
	}

	Vector3f Vector3f::operator/(const float& other)
	{
		return Vector3f(x / other, y / other, z / other);
	}

	Vector3f& Vector3f::operator/=(const Vector3f& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vector3f& Vector3f::operator/=(const float& other)
	{
		x /= other;
		y /= other;
		z /= other;

		return *this;
	}

	bool Vector3f::operator==(Vector3f other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3f::operator!=(Vector3f other)
	{
		return x != other.x || y != other.y || z != other.z;
	}
}