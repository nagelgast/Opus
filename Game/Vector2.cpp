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

Vector2::Vector2(const sf::Vector2f v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(const sf::Vector2f& v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(const sf::Vector2i& v)
{
	x = static_cast<float>(v.x);
	y = static_cast<float>(v.y);
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

Vector2::operator sf::Vector2f() const
{
	return {x, y};
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
