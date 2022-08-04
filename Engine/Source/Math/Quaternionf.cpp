#include <Core.h>
#include "Quaternionf.h"
#include "Vector3f.h"
#include "Matrix4f.h"
#include "MathHelper.h"
#include <cmath>

namespace STL
{
	Quaternionf::Quaternionf()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	Quaternionf::Quaternionf(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	Quaternionf Quaternionf::Normalized()
	{
		return *this / Magnitude();
	}

	float Quaternionf::Dot(const Quaternionf& other)
	{
		return (x * other.x + y * other.y + z * other.z + w * other.w);
	}

	float Quaternionf::Magnitude()
	{
		return std::sqrtf(Dot(*this));
	}

	Quaternionf Quaternionf::Conjugate()
	{
		return Quaternionf(-x, -y, -z, w);
	}

	Quaternionf Quaternionf::Inverse()
	{
		return Conjugate();
	}

	Vector3f Quaternionf::ToEuler()
	{
		float sqW = w * w;
		float sqX = x * x;
		float sqY = y * y;
		float sqZ = z * z;

		float unit = sqX + sqY + sqZ + sqW;
		float test = x * y + z * w;

		float yaw = 0.0f;
		float pitch = 0.0f;
		float roll = 0.0f;

		// North pole singularaty.
		if (test > 0.499f * unit)
		{
			yaw = 2.0f * std::atan2f(x, w);
			pitch = MathHelper::PI * 0.5f;
			roll = 0.0f;

			return Vector3f(yaw, pitch, roll);
		}

		// South pole singularaty
		if (test < -0.499f * unit)
		{
			yaw = -2.0f * std::atan2f(x, w);
			pitch = -MathHelper::PI * 0.5f;
			roll = 0.0f;

			return Vector3f(yaw, pitch, roll);
		}

		yaw = std::atan2f(2.0f * y * w - 2.0f * x * z, sqX - sqY - sqZ + sqW);
		pitch = std::asinf(2.0f * test / unit);
		roll = std::atan2f(2.0f * x * w - 2.0f * y * z, -sqX + sqY - sqZ + sqW);

		return Vector3f(yaw, pitch, roll);
	}

	Matrix4f Quaternionf::ToMatrix4f()
	{
		// Precalculate coordinate products
		float x = this->x * 2.0f;
		float y = this->y * 2.0f;
		float z = this->z * 2.0f;
		float xx = this->x * x;
		float yy = this->y * y;
		float zz = this->z * z;
		float xy = this->x * y;
		float xz = this->x * z;
		float yz = this->y * z;
		float wx = this->w * x;
		float wy = this->w * y;
		float wz = this->w * z;

		Matrix4f mat = Matrix4f::Identity();
		mat.Get(0, 0) = 1.0f - (yy + zz);
		mat.Get(1, 0) = xy + wz;
		mat.Get(2, 0) = xz - wy;
		mat.Get(3, 0) = 0.0f;

		mat.Get(0, 1) = xy - wz;
		mat.Get(1, 1) = 1.0f - (xx + zz);
		mat.Get(2, 1) = yz + wx;
		mat.Get(3, 1) = 0.0f;

		mat.Get(0, 2) = xz + wy;
		mat.Get(1, 2) = yz - wx;
		mat.Get(2, 2) = 1.0f - (xx + yy);
		mat.Get(3, 2) = 0.0f;

		mat.Get(0, 3) = 0.0f;
		mat.Get(1, 3) = 0.0f;
		mat.Get(2, 3) = 0.0f;
		mat.Get(3, 3) = 1.0f;

		return mat;
	}

	Vector3f Quaternionf::RotateVector(const Vector3f& vector)
	{
		float x = this->x * 2.0f;
		float y = this->y * 2.0f;
		float z = this->z * 2.0f;
		float xx = this->x * x;
		float yy = this->y * y;
		float zz = this->z * z;
		float xy = this->x * y;
		float xz = this->x * z;
		float yz = this->y * z;
		float wx = this->w * x;
		float wy = this->w * y;
		float wz = this->w * z;

		Vector3f res;
		res.x = (1.0f - (yy + zz)) * vector.x + (xy - wz) * vector.y + (xz + wy) * vector.z;
		res.y = (xy + wz) * vector.x + (1.0f - (xx + zz)) * vector.y + (yz - wx) * vector.z;
		res.z = (xz - wy) * vector.x + (yz + wx) * vector.y + (1.0f - (xx + yy)) * vector.z;

		return res;
	}

	Quaternionf Quaternionf::operator=(const Quaternionf& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	Quaternionf Quaternionf::operator+(const Quaternionf& other)
	{
		Quaternionf temp = *this;
		temp.x += other.x;
		temp.y += other.y;
		temp.z += other.z;
		temp.w += other.w;

		return temp;
	}

	Quaternionf Quaternionf::operator+(const float s)
	{
		Quaternionf temp = *this;
		temp.x += s;
		temp.y += s;
		temp.z += s;
		temp.w += s;

		return temp;
	}

	Quaternionf& Quaternionf::operator+=(const Quaternionf& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Quaternionf& Quaternionf::operator+=(const float s)
	{
		x += s;
		y += s;
		z += s;
		w += s;

		return *this;
	}

	Quaternionf Quaternionf::operator-(const Quaternionf& other)
	{
		Quaternionf temp = *this;
		temp.x -= other.x;
		temp.y -= other.y;
		temp.z -= other.z;
		temp.w -= other.w;

		return temp;
	}

	Quaternionf Quaternionf::operator-(const float s)
	{
		Quaternionf temp = *this;
		temp.x -= s;
		temp.y -= s;
		temp.z -= s;
		temp.w -= s;

		return temp;
	}

	Quaternionf& Quaternionf::operator-=(const Quaternionf& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Quaternionf& Quaternionf::operator-=(const float s)
	{
		x -= s;
		y -= s;
		z -= s;
		w -= s;

		return *this;
	}

	Quaternionf Quaternionf::operator*(const Quaternionf& other)
	{
		Quaternionf temp;
		temp.x = w * other.x + x * other.w + y * other.z - z * other.y;
		temp.y = w * other.y + y * other.w + z * other.x - x * other.z;
		temp.z = w * other.z + z * other.w + x * other.y - y * other.x;
		temp.w = w * other.w - x * other.x - y * other.y - z * other.z;

		return temp;
	}

	Quaternionf Quaternionf::operator*(const float s)
	{
		Quaternionf temp = *this;
		temp.x *= s;
		temp.y *= s;
		temp.z *= s;
		temp.w *= s;

		return temp;
	}

	Quaternionf& Quaternionf::operator*=(const Quaternionf& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	Quaternionf& Quaternionf::operator*=(const float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}

	Quaternionf Quaternionf::operator/(const Quaternionf& other)
	{
		Quaternionf temp = *this;
		temp.x /= other.x;
		temp.y /= other.y;
		temp.z /= other.z;
		temp.w /= other.w;

		return temp;
	}

	Quaternionf Quaternionf::operator/(const float s)
	{
		Quaternionf temp = *this;
		temp.x /= s;
		temp.y /= s;
		temp.z /= s;
		temp.w /= s;

		return temp;
	}

	Quaternionf& Quaternionf::operator/=(const Quaternionf& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	Quaternionf& Quaternionf::operator/=(const float s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;

		return *this;
	}
}