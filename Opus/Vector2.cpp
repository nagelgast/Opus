#include "Vector2.h"

#include <cmath>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(const float x_in, const float y_in)
{
	x = x_in;
	y = y_in;
}


float Vector2::GetLengthSquared() const
{
	return x * x + y * y;
}

float Vector2::GetLength() const
{
	return sqrt(GetLengthSquared());
}

Vector2 Vector2::GetNormalized() const
{
	const auto length = GetLength();
	if (length > 0)
	{
		return { x / length, y / length };
	}

	return *this;
}

Vector2 Vector2::operator -() const
{
	return {-x, -y};
}


Vector2 Vector2::operator+(const Vector2& right) const
{
	return {x+right.x, y+right.y};
}

Vector2 Vector2::operator -(const Vector2& right) const
{
	return {x-right.x, y-right.y};
}

Vector2 Vector2::operator*(const float right) const
{
	return {x * right, y * right};
}

Vector2 Vector2::operator/(const float right) const
{
	return {x/right, y/right};
}

Vector2 Vector2::operator+=(const Vector2& right)
{
	x += right.x;
	y += right.y;

	return *this;
}
