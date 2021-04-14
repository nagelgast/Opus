#pragma once

#include <SFML/System/Vector2.hpp>

class Vector2
{
public:
	Vector2();
	Vector2(float, float);
	Vector2(const sf::Vector2f v);
	explicit Vector2(const sf::Vector2f& v);
	explicit Vector2(const sf::Vector2i& v);
	float GetLengthSquared() const;
	float GetLength() const;
	Vector2 GetNormalized() const;

	operator sf::Vector2f() const;

	Vector2 operator -() const;

	Vector2 operator +(const Vector2& right) const;
	Vector2 operator -(const Vector2& right) const;
	Vector2 operator *(const float right) const;
	Vector2 operator /(const float right) const;

	float x;
	float y;
};
