#include "Math.h"

Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 result = lhs;
	result += rhs;
	return result;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 result = lhs;
	result -= rhs;
	return result;
}

Vector2 operator*(const Vector2& v, float s)
{
	Vector2 result = v;
	result *= s;
	return result;
}

Vector2 operator*(float s, const Vector2& v)
{
	Vector2 result = v;
	result *= s;
	return result;
}

Vector2 operator/(const Vector2& v, float s)
{
	Vector2 result = v;
	result /= s;
	return result;
}

float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

float Vector2::Length() const
{
	return Math::Sqrt(LengthSquared());
}

void Vector2::Normalize()
{
	(*this) /= (this->Length());
}

Vector2 Vector2::Normalize(const Vector2& v)
{
	Vector2 result = v;
	result.Normalize();
	return v;
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x + a.y * b.y);
}

Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result = lhs;
	result += rhs;
	return result;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result = lhs;
	result -= rhs;
	return result;
}

Vector3 operator*(const Vector3& v, float s)
{
	Vector3 result = v;
	result *= s;
	return result;
}

Vector3 operator*(float s, const Vector3& v)
{
	Vector3 result = v;
	result *= s;
	return result;
}

Vector3 operator/(const Vector3& v, float s)
{
	Vector3 result = v;
	result /= s;
	return result;
}

float Vector3::LengthSquared() const
{
	return x * x + y * y + z * z;
}

float Vector3::Length() const
{
	return Math::Sqrt(LengthSquared());
}

void Vector3::Normalize()
{
	(*this) /= (this->Length());
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	Vector3 result = v;
	result.Normalize();
	return v;
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}