#pragma once
#include <cmath>

namespace Math
{
	const float Pi = 3.1415926535f;

	inline float NearZero(float value, float epsilon = 0.001f)
	{
		if (fabs(value) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Abs(float x)
	{
		return fabsf(x);
	}
}

class Vector2
{
public:
	float x;
	float y;

	Vector2(float x_ = 0.0f, float y_ = 0.0f);
	
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);

	float LengthSquared() const;
	float Length() const;
	
	void Normalize();
	static Vector2 Normalize(const Vector2& v);
	static float Dot(const Vector2& a, const Vector2& b);
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& v, float s);
Vector2 operator*(float s, const Vector2& v);
Vector2 operator/(const Vector2& v, float s);

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f);

	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);

	float LengthSquared() const;
	float Length() const;

	void Normalize();
	static Vector3 Normalize(const Vector3& v);
	static float Dot(const Vector3& a, const Vector3& b);
	static Vector3 Cross(const Vector3& a, const Vector3& b);
};

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator*(float s, const Vector3& v);
Vector3 operator/(const Vector3& v, float s);