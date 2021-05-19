#pragma once

struct Vector2
{
	Vector2();
	Vector2(int, int);
	Vector2(float, float);
	Vector2(int, float);
	Vector2(float, int);
	float GetLengthSquared() const;
	float GetLength() const;
	Vector2 GetNormalized() const;

	Vector2 operator -() const;

	Vector2 operator +(const Vector2& right) const;
	Vector2 operator -(const Vector2& right) const;
	Vector2 operator *(const float right) const;
	Vector2 operator /(const float right) const;
	Vector2 operator+=(const Vector2& right);

	float x;
	float y;
};
