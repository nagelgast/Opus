#pragma once

class __declspec(dllexport) Vector2
{
public:
	Vector2();
	Vector2(float, float);
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
